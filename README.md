![TinyTV Logo](https://i.imgur.com/F3mrsaW.png)
## Inspiration
Have you ever thought to yourself, "man, my head hurts! There are way **too many pixels** on my dang phone!" or "these graphics look **too** realistic!" So have we. That's why we decided to create the world's first 1x1 pixel television. We like to think that the art of film is more about the mood that the director creates and less about the content itself. That sentiment is what led us to design the TinyTV, a simpler TV to take us back to a simpler time.

## What it does
Using a next-generation c++ program, the user can input a video file and a COM port. The program then takes that video file, averages out the pixels on every frame, displays it, and then sends the average color data via USB serial port to the TinyTV. The TinyTV code then receives that data and converts it to color output. It's like magic! 

## How we built it
We build the TinyTV using 3D-printed plastic, an RGB LED, an Arduino, and lots of love. We also utilized C++ (with CMake) to build the driver application.

## Challenges we ran into
We spent a lot of time trying to get our driver application to spit out serial data that would be recognized by the TinyTV. After using some port-monitoring software, we discovered that our buffer size was a couple of bytes too big, leading to an excess of garbage information being sent across the line. Oops! We also wasted a lot of time watching Ocean's 11 on our TinyTV, so maybe we shouldn't have done that. Ah, well. I guess the TinyTV is just *too* enticing and awesome.

## Accomplishments that we're proud of
One of us didn't know C++ and two of us didn't have access to the physical TinyTV. I'm proud of our ability to work together online and still get a working physical product even when we're miles apart.

## Build it yourself
```bash
# make sure you have OpenCV and CMake installed. :)
git clone https://github.com/PRUGCodes/TinyTV.git
cd TinyTV
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## What's next for TinyTV
Perhaps a wireless TinyTV is in order... You could watch it while you're biking! You could watch it while you're at school! You could watch it in the car! The possibilities are endless!
