# RayTracer

This is an update of the raytracer skeleton from the book "Raytracing from the Ground Up" by Kevin Suffern..

# Why?

* I'm not a fan of wxWidgets - in my experience, Qt has been a lot more stable with it's API and is better suited
  for portable applications where the UI doesn't need significant adaptation between platforms.

* There's a lot of legacy C++ style in the codebase that simply shouldn't be there.

* I wanted a starting point that was going to be lower-fuss to flip between Linux and Windows - the platforms I do
  the bulk of my coding on.

* I wanted to get these distractions out of the way before I got into the meat of the book. :)

# (Intended) Changes

- Switch to Qt5 to achieve one codebase for all platforms.

- Tidy up C++ style to be more C++11/14 compliant.

- Switch from classic object pointers to using C++11 `shared_ptr`/`weak_ptr` where suitable

# Status

Incomplete (so far) - I'm still half-way through remapping the old Wx UI to a Qt one, then I'll tidy up
C++ syntax.

