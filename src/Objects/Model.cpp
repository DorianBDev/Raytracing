#include "Model.h"

#include "Utils/Math.h"

#include <limits>

Model::Model(Material material,
             const Color& color,
             const std::string& path,
             const Vector3& coordinates,
             const Vector3& angle,
             double scale)
    : Object(material, color),
      m_origin(coordinates),
      m_angle(angle),
      m_scale(scale)
{
    readFile(path);
}

void Model::readFile(const std::string& path)
{
    std::vector<Vector3> coordinatesList;
    std::vector<Vector3> normalList;

    Vector3 coordinates;
    Vector3 a;
    Vector3 b;
    Vector3 c;

    std::stringstream stream;
    std::string line;
    std::string word;
    std::string index;

    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Error when opening the file.");

    while (getline(file, line))
    {
        stream = std::stringstream(line);
        getline(stream, word, ' ');

        if (word == "v")
        {
            coordinates = split(line, ' ');

            coordinates = coordinates * m_scale;
            coordinates = coordinates.rotateX(m_angle.x()).rotateY(m_angle.y()).rotateZ(m_angle.z());

            coordinatesList.emplace_back(coordinates + m_origin);
        }
        else if (word == "vn")
        {
            coordinates = split(line, ' ');
            coordinates = coordinates.rotateX(m_angle.x()).rotateY(m_angle.y()).rotateZ(m_angle.z());

            normalList.emplace_back(coordinates);
        }
        else if (word == "f")
        {
            getline(stream, word, ' ');
            a = split(word, '/');
            getline(stream, word, ' ');
            b = split(word, '/');
            getline(stream, word, ' ');
            c = split(word, '/');

            m_triangle.emplace_back(Materials::metal(),
                                    Color(50, 50, 50),
                                    coordinatesList[static_cast<int>(a.x() - 1)],
                                    coordinatesList[static_cast<int>(b.x() - 1)],
                                    coordinatesList[static_cast<int>(c.x() - 1)],
                                    normalList[static_cast<int>(a.z() - 1)]);
        }
    }
    file.close();
}

Vector3 Model::split(const std::string& line, char delimiter)
{
    std::string tmp = std::regex_replace(line, std::regex("//"), "/");

    std::stringstream stream(tmp);
    std::string word;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    if (delimiter == ' ')
        getline(stream, word, delimiter);

    getline(stream, word, delimiter);
    x = std::stod(word);

    if (line == tmp)
    {
        getline(stream, word, delimiter);
        y = std::stod(word);
    }
    else
        y = 0;

    getline(stream, word, delimiter);
    z = std::stod(word);

    return {{x, y, z}};
}

std::optional<Vector3> Model::getIntersection(const Ray& ray) const
{
    std::vector<Vector3> intersectionList;
    std::optional<Vector3> intersection;

    const Vector3& origin = ray.getOrigin();

    double distance = 0.0;
    double max = std::numeric_limits<double>::max();

    for (const auto& triangle : m_triangle)
    {
        intersection = triangle.getIntersection(ray);

        if (intersection != std::nullopt)
            intersectionList.emplace_back(intersection.value());
    }

    if (intersectionList.empty())
        return std::nullopt;

    for (const auto& intersectionPoint : intersectionList)
    {
        distance = intersectionPoint.distance(origin);

        if (distance < max || areDoubleApproximatelyEqual(distance, max, 0.00000001))
        {
            intersection = intersectionPoint;
            max = distance;
        }
    }

    return intersection;
}

std::optional<Ray> Model::getSecondaryRay(const Vector3& intersectionPoint, const Vector3& originLight) const
{
    return Ray(intersectionPoint, originLight - intersectionPoint, SECONDARY);
}

Vector3 Model::getNormal(const Vector3& intersectionPoint) const
{
    std::vector<Vector3> normalList;

    for (const auto& triangle : m_triangle)
    {
        if (triangle.isInTriangle(intersectionPoint))
        {
            normalList.emplace_back(triangle.getNormal(intersectionPoint));
        }
    }

    Vector3 bestNormal(0, 0, 0);

    if (normalList.size() == 1)
        return normalList.at(0);

    std::cout << normalList.size() << std::endl;

    for (const auto& normal : normalList)
    {
        bestNormal += normal;
    }

    return bestNormal * -1;
}
