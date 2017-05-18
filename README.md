# Odin

The [Talisker](https://github.com/TaliskerPlatform/) [nanokernel](https://en.wikipedia.org/wiki/Microkernel#Nanokernel).

[![Current build status][travis]](https://travis-ci.org/TaliskerPlatform/Odin.app)
[![Apache 2.0 licensed][license]](#license)
![Implemented in C][language]

## Introduction

Odin is the Talisker nanokernel. On its own, it’s somewhat less useful than
MS-DOS. It has no memory protection or virtual memory, no multitasking,
absolutely minimal hardware abstraction, and barely any I/O capabilities.

It does, however, incorporate a console, the ability to spawn tasks in the form
of ELF executables, use a bootloader-provided `ar`-format archive as a simple
RAMdisk, and defines the interfaces between components of the system, as well
as the means of communicating with them and replacing them on the fly.

The "replacing them on the fly" aspect is intrinsic to the operation of the
system: memory protection and virtual memory are provided by a separate
application. When it’s executed as a privileged process (such as when the system is first booted and no memory protection is in place yet), Odin provides the interface that it can use to register itself as the arbiter of the address space—and with exclusive control over the mapping and protection levels of the various regions that are in use.

The same applies to process scheduling: Odin itself provides a single-tasking
environment, but has a conceptual view of tasks and threads and provides the
mechanisms to interact with them. However, the built-in implementation of a
process scheduler will only ever run one thread at a time, and it will
continue to execute until it reaches its conclusion. Similarly to the memory
manager, the process scheduler can be loaded, and it will take responsibility
for the multitasking features of the system.

Access to privileged CPU contexts and address space is governed by the process scheduler and memory manager. This means that it can be granted as needed, rather than having separate kinds of executable — kernel modules or extensions, versus ordinary daemons.

While care must be taken in user-space to ensure that rogue applications aren’t able to wreak havoc, the same applies to any modern operating system with a modular kernel.

### Kernel objects and system calls

All Odin objects follow the COM patterns and binary interface rules. Within the context of a task, file descriptors — or rather *object descriptors* — are actually just reference-counted handles to COM interface pointers. Under normal circumstances, descriptors 0, 1, and 2 would indeed be descriptors to objects which support character I/O calls, just as a file descriptors represent, but in principle any descriptor could refer to any type of object whose internal implementation is in a separate address-space from the user's. 

All system calls take two fixed parameters: a numeric object descriptor, and a method index. Upon a call being despatched within Odin, it locates the interface pointer referred to by that object descriptor, and invokes the function pointer in the interface's method table matching the method index, passing it the remaining system call paramters. As all function pointers in the table are the same size, so the depatch handler can simply treat it as an array of word-returning varargs-accepting function pointers.

For any interface pointer whose class implementation is within Odin's privileged address space, this *marshaling* of the method call via a system call interface is easily comparable to any call in a modern operating system which operates on a target object of some kind—particularly filesystem calls, because filesystem interfaces tend to be heavily abstracted to allow for extensibility, such as new filesystem drivers being enabled without recompiling the kernel.

### Inter-process communication

Where the caller, Odin, and class implementation are in different address spaces, the system call mechanism doubles as a transparent inter-process communication mechanism. Rather than the object descriptor pointing directly
to the implementation, it can point to a marshaler instead. A marshaler is a special kind of instance which simply forwards method calls somewhere else and returns whatever the result was back to the caller. In this case, the object descriptor would point to a marshaling instance which passes the call on to the thread which is providing the implementation.

Indeed, all object descriptors actually point to a marshaler of one sort or another, for two reasons. Most importantly, to insulate reference-counting of the kernel object from user-space reference counting (an object descriptor needs to know when it shouldn’t exist any more, but there can be multiple descriptors in different tasks for the same instance).

Second, in order to pass parameters which are pointers, or other object
descriptors, through a system call boundary, something needs to know which regions of memory constitute parameter buffers, and of course how big they are and how to access them. This applies again, with a little more complexity, when making IPC calls from the privileged context within Odin out to an unprivileged user-space task providing some kind of capability.

The rules regarding buffer translation differ from interface to interface (because each has different sets of methods accepting different kinds of parameters), but the Talisker IDL compiler will generate the relevant user-space stubs and the data required for Odin's marshaler to do its job properly. All interfaces are identified by a UUID, and Odin's marshaler tracks the UUID of the interface against the pointer it has so that it look up the correct marshaling data for that interface. If the data isn't available, then all method calls except those from `IUnknown` will fail.

### Access control at marshaling boundaries

The `queryInterface()` method of `IUnknown` is implemented by all COM classes; it is guaranteed by the ABI to be the first pointer in the method table, and always have a consistent method signature.

In Odin’s marshaling scheme, any interface pointer *returned* by a method call is assigned a new object descriptor whose value is returned to the caller—its own marshaling logic can create a new marhsalling instance wrapped around the newly-returned file descriptor.

Because of this, any interface pointer returned by a call to `queryInterface()` will result in a new object descriptor being created for the task.

Therefore, if the interfaces for read-only versus read-write access are *different*, then a marshaler within Odin could invoke logic prior to perform access-control checks before the real `queryInterface()` implementation is invoked.

In effect, then, within Odin itself, any kind of access control is represented by a principal (some object that requires access to something) and the IID of the interface on the target object to which access should be granted.

A side-effect of this is that the unit of access control can be almost anything—an interface is simply a set of operations a caller can perform on an object, so it is logical that this *is* the fundamental unit of access control.

### The task descriptor

Every task is always launched with a minimum of one object descriptor assigned to it (although usually more), which points to the task's own interface pointer. This descriptor's marshaler will refuse to allow the descriptor to be closed from user-space; requests to inherit the descriptor into a child process will always fail, although a child process can be given access to the parent's by cloning the task descriptor and marking the resulting interface as being inheritable.

### The thread descriptor



### The object namespace

Any COM object can be placed into the global object namespace by linking it to an object directory container by establishing an in-memory a *directory entry* instance for it, which represents the name, type, ownership, notional size, and ACLs of the target object within that directory.

Filesystem operations consist of traversing and manipulating this tree of object directories: Odin provides a transient in-memory root object directory, analogous to the root filesystem in Unix-like systems. This transient directory supports the creation of directory *entries* to represent running objects, but doesn’t have any capabilities to store any data: in other words, it supports creating subdirectories, symbolic links, device nodes, and so on, but not "real" files.

Real filesystem implementations provide instances which implement the same object directory interfaces, but whose data is read from disk as needed; mounting a filesystem is therefore a case of initialising a filesystem object (supplying it with the block device object), obtaining its object directory interface, and creating a directory entry for it at the mount-point.

The root object directory has the following structure:

    /
        Volumes
		    [mount points are generally created here]
			[root volume]
				Local
					Applications
					Library
						Preferences
						Caches
						: (see /Volumes/Root/Talisker/Library, below)
					Users
						sara
						joe
						admin
							Applications
							Desktop
							Pictures
							Movies
							Music
							Downloads
							Library
							    :
				Talisker
					Applications
						Utilities
					Library
						Preferences
						Desktop Pictures
						Fonts
						Personalities
						UserTemplate
						Sounds
						
			Boot [initial RAMdisk]
			Root → [root volume]
		Devices
		    [device nodes are automatically created here]
		Local → /Volumes/Root/Local
		Network
		    Applications → [mounted network share]
		    Library → [mounted network share]
			Users → [mounted network share]
			Servers
			    [domain]
				    [share]
				    [host]
					    [share]
		Talisker
		    Applications → /Volumes/Root/Talisker/Applications
			Library → /Volumes/Root/Talisker/Library
			System
				Classes
					[class uuid] → [class factory instance or executable]
					[name] → [class uuid]
				Interfaces
					[uuid]
						ImplementedBy
							[class uuid]
				Subsystems
					[uuid]
				ContentTypes
					application
						x-unknown
							Extensions
								bin
					image
						jpeg
							Extensions
								jpg
					Extensions
						jpg → [MIME type entry for image/jpeg]
					
				Tasks
					me → [link to PID of invoker]
					[pid]
						name
						environment
						cmdline
						state
						priority
						Threads
							[tid]
								state
									

Because objects are polymorphic and are generally-accessible via RPC, the directory entries within `/Talisker/System/Tasks` refer not to synthesised files in a virtual filesystem, but the Odin’s own representations of each task: "opening" one of those tasks within the directory is actually just obtaining an object descriptor for that task.

For example, imagine that our IDirectory interface has a `resolve` method which parses a path, traversing the tree, and returns an IDirectoryEntry interface pointer if one is found. "Opening" the "file" that it refers to is simply a case of calling a method on the directory entry to obtain an interface pointer from the retained object.

The resolve method might look like this:

    int IDirectory::resolve(const char *path, IDirectoryEntry **result);

while the method to open a directory entry might look like this:

	int IDirectoryEntry::open(const uuid_t iid, void **result);

Given a thread has a current working directory, and a thread can always access its own thread interface via the thread descriptor, a traditional "open" call could look a little like this:

    int
	open(const char *path, int flags, ...)
	{
		uuid_t iid;
		IDirectory *cwd;
		IDirectoryEntry *de;
		IUnknown *file;
		
		/* The access bits determine which interface we're going to request */
		if(flags & O_RDWR)
		{
			iid = IID_IReadWriteFile;
		}
		elif(flags & O_RDONLY)
		{
			iid = IID_IReadFile;
		}
		else
		{
			iid = IID_WriteFile;
		}
		
		/* omitting code to deal with appending, truncating, or creating
		 * new files!
		 */
    
		/* use the thread API to obtain a reference to the current working directory */
		if(self->cwd(&cwd)) 
		{
			/* somehow we don't have a valid CWD */
			/* errno will be set for us */
			return -1;
		}
		r = cwd->resolve(path, &de))
		{
			/* errno will be set for us */
			cwd->release();
			return -1;
		}
		cwd->release();
		if(de->open(iid, (void **) &file))
		{
			de->release();
			return -1;
		}
		de->release();
		return self->descriptor(file);
	}

### Subsystems

Although the sequence above broadly matches what most traditional operating systems do in response to an open() call, it is nevertheless true that if in an Odin-based system each of these calls is an IPC, possibly involving multiple context switches, then performance will probably not compare favourably to other systems for performing similar operations.

Odin's philosophy is not one of reducing the footprint of the system at the expense of performance or capability, but to reduce the footprint *in order to maximise flexibility*.

Rather than that this call sequence necessarily being executed in user-mode, consider that it could be encapsulated into an interface providing a certain API: for example, ISO C’s standard I/O calls.

While this call *could* be serviced via a library which is able to run solely in user-mode, there would undoubtedly be a performance increase if an `open()` call was marshaled via an object descriptor into a method call whose implementation had direct access to the same memory space as Odin's methods that it calls.

In Odin, the formalised mechanism for achieving this is through *subsystems*. When executed with sufficient privilege, a subsystem task can request that it be converted to a kernel-mode task (if it isn't already), so that it can avoid context-switch penalties. Once elevated to kernel-mode, a subsystem's existence is advertised via `/Talisker/System/Subsystems` as well as a method on the task interface.

### Advertising capabilities

Classically, clients of COM objects are only aware of the interfaces that they know about, and won't tend to have a preferred list of interfaces which certain objects would ideally support—even if they do, they still need to query for each separately to determine availability.

Because instances within the namespace are essentially advertising themselves, they also a need a mechanism to advertise what they *are*—or rather, what interfaces they support.

To do this, objects can expose the `ISupports` interface, which provides a single method, `supports()`, which a client can use to query an instance for what *other* interfaces it supports (or at least those which it is willing to advertise the availability of).

### Interpreters

Interpreters are special kinds of proxy classes which allow an object supporting one interface to support another interface that it does not natively support itself.

For example, an interpreter can be used to allow a JSON file on disk to support being opened and providing a Dictionary (a set of key-value pair) interface, or an image metadata interface be opened on a JPEG image file.

Interpreters are used to allow files on disk to be executable: all executables supported by a running system, whether they're scripts, binaries, or something else, are executed by way of their IExecutable inteface.

Interpreters bind a matching rule to a class implementation that they provide and the interface UUID provided by that class: the matching rule is a combination of the UUID of a the interface, and if it's a file, include constraints on file access bits (e.g., is the execute bit set?), or on content type (which may be defined by filename pattern, magic numbers, or present in filesystem metadata).

They provide a class which implements `IInterpreterFactory`-a type of class factory which initialises a wrapper around the interface provded.

For example, a [Mach-O](https://en.wikipedia.org/wiki/Mach-O) executable interpreter might register itself as follows:

	Provides:         IID_IExecutable
	Matches:
	    Interface:    IID_IFile
		File access:  IID_ExcutableFile
		Signature:
			0: <CF> <FA> <ED> <FE>
			1: <CE> <FA> <ED> <FE>
			2: <CA> <FE> <BA> <BE>
		

When `queryInterface()` is invoked on an object advertising `IFile`, and the interface requested is `IExecutable`, and one of the three provided binary signatures match, then the ELF interpreter's factory’s `interpreterInstance()` method is invoked:

	int interpreterInstance([in] const uuid_t inneriid, [in,iid_is(inneriid)] void *innerobject, [in] const uuid_t interpiid, [out,iid_is(interpiiid)] void **interpreter);

In this case, it would be invoked with:

	factory->interpreterInstance(IID_IFile, fileobject, IID_IExecutable, &ptr);

From the perspective of the user of the object descriptor, this is completely transparent: all executable Mach-O files appear to natively support the IExecutable interface, allowing them to be executed in a task.

### Built-in device drivers

#### Character devices

##### Maintenance console

If enabled, Odin has the capability to use a serial a serial console for log output, defaulting to 9600,8,N,1.

If Odin is running in user-space on a host operating system, a “host console” which sends output to standard error is provided instead.

#### Filesystems

##### Archive filesystem

#### Interpreters

##### ELF interpreter

The ELF interpreter provides a loader capable of presenting an `IExecutable` interface to any ELF executable for a supported architecture and ABI that is accessible as a executable `IFile`.

Unlike other interpreter classes, the ELF interpreter is compiled in to Odin on most systems, and so the initial set of tasks which are launched at system start-up (prior to interpreters for any other executable formats being launched) must also be ELF binaries.

## Building from source

## Running Odin

### Deployment scenarios

For desktops and servers, the envisaged deployment scenario is as a dom0 kernel beneath a hypervisor, allowing personalities to launch VMs to provide whatever high-level capabilities (running Linux or Windows applications, for example) might be required.

On more constrained systems, a hypervisor may not be feasible, and instead Odin runs on bare-metal. On systems without an MMU, a different memory manager could be employed—or even left to the rudimentary management Odin itself performs.

Odin is intended to be small, portable and extensible enough to be able to form a useful basis for operating systems running on everything from IoT devices to midrange and mainframe systems.

## License

Copyright © 2017 Mo McRoberts.

Licensed under the terms of the [Apache License, Version 2.0](http://www.apache.org/licenses/LICENSE-2.0).

[travis]: https://img.shields.io/travis/TaliskerPlatform/Odin.app.svg
[license]: https://img.shields.io/badge/license-Apache%202.0-blue.svg
[language]: https://img.shields.io/badge/implemented%20in-C-yellow.svg