// cli/main.cpp
//
// Main for CLI operation mode

#include <thread>
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

#include "../World/World.h"
#include "ImageTarget.h"

using namespace std;

int
main(int argc, char **argv)
{
    unsigned int desired_threads = thread::hardware_concurrency();
    cout << "using " << desired_threads << " threads" << endl;

    auto start_time = chrono::steady_clock::now();

    auto theWorld = make_shared<World>();
    cout << "Building world..." << endl;
    theWorld->build();

    ImageTarget target(800,800);
    theWorld->paintArea = &target;

    cout << "Rendering..." << endl;

    std::vector<std::thread *> threads(desired_threads, nullptr);

    auto render_start_time = chrono::steady_clock::now();

    for (int t = 0; t < desired_threads; t++) {
        threads[t] = new std::thread([=](int thread){theWorld->camera_ptr->render_scene(*theWorld, thread, desired_threads);}, t);
    }

    cout << "waiting for rendering threads to finish..." << endl;
    for (int t = 0; t < desired_threads; t++) {
        threads[t]->join();
    }

    auto render_finish_time = chrono::steady_clock::now();

    cout << "writing output file" << endl;
    if (!target.saveImage("render.png")) {
        cout << "Got an error writing the file" << endl;
        return 1;
    }

    auto all_finshed_time = chrono::steady_clock::now();


    chrono::duration<double> full_time = all_finshed_time - start_time;
    chrono::duration<double> render_time = render_finish_time - render_start_time;

    cout << "Done." << endl;
    cout << "Timer Resolution is " << chrono::steady_clock::period::num << ":" << chrono::steady_clock::period::den << std::endl;
    cout << "Total Process Time: " << full_time.count() << " seconds" << endl;
    cout << "Rendering Time: " << render_time.count() << " seconds" << endl;

    return 0;
}