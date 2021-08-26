# Doorbell camera example

This example is a simple door bell camera application based on the person detection example.
The camera connected which is connected to the ESP chip captures surrounding images continuously.The tensorflow model running on the esp chip detects if a person is present infront of the camera.When a person is detected the ESP chip sends an emailto notify the user along with the image of the person captured from the camera.
The email configurations can be done through [Configure the Example](./README#configure-the-example)

This example shows how you can use Tensorflow Lite to run a 250 kilobyte neural
network to recognize people in images captured by a camera.It also sheds some light on how a complex application with multiple operations can be run on the [ESP-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md).

## Running on the ESP-EYE

The following instructions will help you build and deploy this sample to
[ESP-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)
using the [ESP IDF](https://github.com/espressif/esp-idf).

The sample has been tested on ESP-IDF version 4.0 with the following devices: -
[ESP-EYE](https://github.com/espressif/esp-who/blob/master/docs/en/get-started/ESP-EYE_Getting_Started_Guide.md)

ESP-EYE is a board which has a built-in camera which can be used to run this
example, if you want to use other esp boards you will have to connect camera
externally and write your own
[image_provider.cc](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/doorbell_camera/esp/image_provider.cc).
and
[app_camera_esp.c](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/doorbell_camera/esp/app_camera_esp.c).
You can also write you own
[detection_responder.cc](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/doorbell_camera/detection_responder.cc).

### Install the ESP IDF

Follow the instructions of the
[ESP-IDF get started guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html)
to setup the toolchain and the ESP-IDF itself.

The next steps assume that the
[IDF environment variables are set](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#step-4-set-up-the-environment-variables) :

*   The `IDF_PATH` environment variable is set
*   `idf.py` and Xtensa-esp32 tools (e.g. `xtensa-esp32-elf-gcc`) are in `$PATH`
*   `esp32-camera` should be downloaded in `components/` dir of example as
    explained in `Building the example`(below)

### Generate the examples

The example project can be generated with the following command:
`make -f tensorflow/lite/micro/tools/make/Makefile TARGET=esp generate_doorbell_camera_esp_project`

  - On mac I have seen issues with `make`. Please use `gmake` if you happen to be so.

### Building the example

Go the the example project directory

`cd tensorflow/lite/micro/tools/make/gen/esp_xtensa-esp32/prj/doorbell_camera/esp-idf`

As the `doorbell_camera` example requires an external component `esp32-camera`
for functioning hence we will have to manually clone it in `components/`
directory of the example with following command.
`git clone https://github.com/espressif/esp32-camera.git components/esp32-camera`
`git checkout eacd640b8d379883bff1251a1005ebf3cf1ed95c`

Configure camera and email credentials
  - Run `idf.py menuconfig`
  - You will be presented with Camera config and SMTP config menus.
  - Please setup values appropriately.

Then build with `idf.py`: `idf.py build`

## Configure the example

The project configuration menu can be opened with following command,
```
idf.py menuconfig
```
### i) Wifi Configuration
Wifi or Ethernet can be configured under the "Example Connection Configuration" menu of the project configuration menu.
It includes following two things
* *SSID* - SSID of the wifi network to which ESP device is to be connected.
* *Password* - Password of the wifi network.

### ii) SMTP Configuration
The SMTP configuration can be done under the "SMTP Configuration" menu of the project configuration menu.
It includes setup of following things,
* Mail server - the mail server which used by the SMTP client( the default is `smtp.googlemail.com`)
> By default CA certificate of `smtp.googlemail.com` is provided in SMTP client component, you will also need to update the CA certificate if you wish to change the mail server
* Mail port number - the mail port number for the example to connect to ( default is `587` )
* Sender email - Sender's email address
* Sender password - Sender's email password
* Reciepient email - Reciepients email address
> For the SMTP client on the ESP deivce to be able to send mail, access for the less secure apps must be turned on for the email address of the sender.Please visit to [Less secure apps & your Google Account](https://support.google.com/accounts/answer/6010255) for more details.

### Load and run the example

To flash (replace `/dev/ttyUSB0` with the device serial port): `idf.py --port
/dev/ttyUSB0 flash`

Monitor the serial output: `idf.py --port /dev/ttyUSB0 monitor`

Use `Ctrl+]` to exit.

The previous two commands can be combined:
`idf.py --port /dev/ttyUSB0 flash monitor`

When a person is detected (One inference is done in about 1 second), the
captured image is sent to email using configuration provided in build step.
