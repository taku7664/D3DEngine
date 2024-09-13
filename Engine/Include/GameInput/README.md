Overview of GameInput (https://aka.ms/gameinput)

GameInput is a next-generation input API that exposes input devices of all kinds through a single consistent interface.
It's designed with a simple programming model that makes it easy to use. GameInput is built from the ground up for the
best possible performance. Key features of the GameInput API are as follows.

*   Availability:

    GameInput is available on PC and Xbox via the GDK. Older versions of Windows going back to Windows 10 19H1 (May 2019
    update) are supported. PC support (including earlier versions of Windows) will be available in an upcoming Windows
    SDK.

*   Consistency:

    GameInput exposes input from keyboards, mice, gamepads, and other game controllers via a single unified input model,
    synchronized to a common time base. The code for handling input from these devices is nearly identical, using many
    of the same functions but with different filters applied. This makes it easy to add support for additional input
    devices, without major changes to input code.

*   Functionality:

    GameInput is a functional superset of all legacy input APIs—XInput, DirectInput, Raw Input, Human Interface Device
    (HID), and WinRT APIs—in addition to adding new features of its own. GameInput's functionality ranges from simple
    fixed-format gamepad state to detailed low-level raw device access. Input can be obtained via polling or callbacks
    in an event-driven way. Haptics and force feedback are fully supported, and third-party device SDKs can easily be
    written on top of GameInput to provide access to custom device features.

*   Performance:

    GameInput is built around an entirely new direct memory access (DMA) architecture for the lowest possible input
    latency and resource usage. Nearly all API functions are lock-free with strict performance guarantees, while still
    being 100 percent thread-safe. This makes them safe to call from time-sensitive contexts such as render threads.
    Advanced applications can take direct control of scheduling GameInput's internal asynchronous work queues,
    controlling which thread does the work and how often.

*   Usability

    GameInput was designed with ease of use as a top priority. Most common input tasks can be implemented with just a
    few lines of code.
