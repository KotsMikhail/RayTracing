#include "scene.h"

namespace RayTracing
{

    void Scene::load(const std::string& path, ColorType ctype, const boost::any& param)
    {
        YAML::Node config = YAML::LoadFile(path);
        m_camera.load(config);

        YAML::Node scene = config["scene"];
        for (auto i = scene.begin(); i != scene.end(); i++)
        {
            YAML::Node node = (*i);
            if (node["node"])
            {
                Node* object = getObject(node["node"], ctype, param);
                m_objects.push_back(object);
            }
            else if (node["light"])
            {
                Light* light = new Light(node["light"], m_camera.position());
                m_lights.push_back(light);
            }
            else
                throw std::runtime_error("Unknown node type");
        }
    }

    Bitmap Scene::render(int resolutionX, int resolutionY, int traceDepth) const
    {
        Bitmap result(resolutionX, resolutionY);

        Point point;
        for (int x = 0; x < resolutionX; x++)
            for (int y = 0; y < resolutionY; y++)
            {
                Ray ray = m_camera.getCameraRay((double)x / resolutionX, (double)y / resolutionY);
                Node* object = getRayIntersection(ray, point);
                result.set(x, y, getIntersectionColor(object, ray, point, traceDepth));
            }

        return result;
    }

    Node* RayTracing::Scene::getRayIntersection(const Ray& ray, Point& point) const
    {
        Node* object = nullptr;
        point = { std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max() };

        for (auto obj = m_objects.begin(); obj != m_objects.end(); obj++)
        {
            std::vector<Point> intersections = (*obj)->rayIntersetion(ray);
            for(auto newPoint = intersections.begin(); newPoint != intersections.end(); newPoint++)
                if (m_camera.checkVisibility(point, *newPoint))
                {
                    point = *newPoint;
                    object = *obj;
                }
        }

        return object;
    }

    Point RayTracing::Scene::getIntersectionColor(const Node* object, const Ray& ray, const Point& point, int traceDepth) const
    {
        Point color = BACKGROUND;

        if (object)
        {
            color = object->color()->getColor(point);
            Point illumitation = { 0.0, 0.0, 0.0 };
            Point pointBiased = point + object->normal(point) * 1e-5;
            Point normal = object->normal(point);
            for (auto light = m_lights.begin(); light != m_lights.end(); light++)
            {
                Point p;
                bool shaded = getRayIntersection((*light)->getLightRay(pointBiased), p) != nullptr;
                illumitation = illumitation + (*light)->getIllumination(pointBiased, normal, *object, shaded);
            }
            illumitation.clamp(0.0, 1.0);
            color = { color.x * illumitation.x, color.y * illumitation.y, color.z * illumitation.z };

            if (object->reflection() && traceDepth)
            {
                Ray reflectedRay = ray.reflect(pointBiased, normal);
                Point newPoint;
                Node* newObject = getRayIntersection(reflectedRay, newPoint);
                color = color * (1 - object->reflection()) + getIntersectionColor(newObject, reflectedRay, newPoint, traceDepth - 1) * object->reflection();
            }
        }

        return color;
    }

    Node* Scene::getObject(const YAML::Node& node, ColorType ctype, const boost::any& param) const
    {
        Node* object;

        if (node["sphere"])
            object = new Sphere();
        else if (node["cylinder"])
            object = new Cylinder();
        else if (node["plane"])
            object = new Plane();
        else if (node["triangle"])
            object = new Triangle();
        else
            throw std::runtime_error("Unknown graphical primitive");

        object->load(node);
        
        Color* color = nullptr;
        double maxDist = 0.0;
        switch (ctype)
        {
        case ColorType::MATERIAL:
            color = new MaterialColor(node);
            break;
        case ColorType::NORMAL:
            color = new NormalColor(object);
            break;
        case ColorType::DISTANCE:
            maxDist = boost::any_cast<double>(param);
            color = new DistanceColor(m_camera.position(), maxDist);
            break;
        default:
            throw std::runtime_error("Unsupported color type");
            break;
        };
        object->color() = color;

        return object;
    }

}