# Hello World Flipper Application Package

This is the source code for a simple flipper application package (fap). This program is not very
interesting but it can be used a skeleton to build more interesting applications.

This should work on any varient of the flipper firmware that supports EXTERNAL applications.
However, I only tested this on [Unleashed](https://github.com/DarkFlippers/unleashed-firmware). The
quick start will use Unleashed but you should be able to use the
[Official Firmware](https://github.com/flipperdevices/flipperzero-firmware) with the same steps.

## Quick Start

Pull the unleashed firmware. I needed, you should install the firmware on your device. You can see
how to do that in the [Unleashed Installation Documentation](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md).

```bash
git clone https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Next, clone this repo into the applications_user directory. The directory name `hello_app` is
important. This name has to match the app_id as defined in `application.fam.`

```bash
git clone https://github.com/en0/hello_flipper.git applications_user/hello_app
```

Optionally, build the fap.

```bash
./fbt faps
```

Lastly, plugin you flipper and install the fap.

```bash
./fbt launch_app APPSRC=applications_user/hello_app
```

## Troubleshooting

__launch_app hangs on `Installing` or you get the error `Unexpected reason: Can't start, Applications
application is running`.__

Make sure your flipper is on the desktop and try again.

__You get the error `could not open port /dev/ttyACM0: [Errno 16] Device or resource busy: '/dev/ttyACM0'`__

Make sure qFlipper is not running and that you have permission to access the serial device.

## Other Notes

You can see your installed application under the `Applications` menu. To remove the fap, use
qFlipper's file manager to delete it from the `Apps` directory.

# Resources

- [Apps On SD Cards](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/AppsOnSDCard.md)
- [Offical](https://github.com/flipperdevices/flipperzero-firmware)
- [Unleashed](https://github.com/DarkFlippers/unleashed-firmware)

