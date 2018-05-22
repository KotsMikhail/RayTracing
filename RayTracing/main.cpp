#include <iostream>
#include <boost/program_options.hpp>

#include "scene.h"
#include "bitmap.h"
#include "color.h"

namespace bo = boost::program_options;

int main(int argc, const char *argv[])
{
    bo::options_description desc{ "Options" };
    desc.add_options()
        ("help,h", "Help screen")
        ("scene,s", bo::value<std::string>(), "Yaml file with scene structure")
        ("resolution_x,x", bo::value<int>()->default_value(1024), "Image resolution against X axis")
        ("resolution_y,y", bo::value<int>()->default_value(1024), "Image resolution against Y axis")
        ("output,o", bo::value<std::string>(), "Output rendered image")
        ("trace_depth,d", bo::value<int>()->default_value(2), "Trace depth")
        ("normal_as_color", "Output normal as color")
        ("distance_as_color", "Output distance as color")
        ("dist_range", bo::value<double>()->default_value(30.0), "Maximum distance for distance as color");

    /*try
    {*/
        bo::variables_map vm;
        bo::parsed_options parsed = bo::command_line_parser(argc, argv).options(desc).run();
        bo::store(parsed, vm);
        bo::notify(vm);

        if (vm.count("help"))
            std::cout << desc << std::endl;
        else
        {
            RayTracing::ColorType ct = RayTracing::ColorType::MATERIAL;
            boost::any param = nullptr;
            if (vm.count("normal_as_color"))
                ct = RayTracing::ColorType::NORMAL;
            else if (vm.count("distance_as_color"))
            {
                ct = RayTracing::ColorType::DISTANCE;
                param = vm["dist_range"].as<double>();
            }

            RayTracing::Scene scene;
            scene.load(vm["scene"].as<std::string>(), ct, param);
            RayTracing::Bitmap image = scene.render(vm["resolution_x"].as<int>(), vm["resolution_y"].as<int>(), vm["trace_depth"].as<int>());
            image.save(vm["output"].as<std::string>());
        }            
    /*}
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }*/

    return 0;
}