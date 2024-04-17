#include "./map.h"

struct CapitalAndClimate
{
    string capital;
    string climate;
};

/**
 * Retrieves the capital and climate information for a given department from a map.
 *
 * @param map The map containing the department-capital and climate information.
 * @param department The department for which to retrieve the information.
 * @return The CapitalAndClimate object containing the capital and climate information for the department.
 */
CapitalAndClimate getCapitalAndClimate(Map<string, CapitalAndClimate> &map, string department)
{
    return map.get(department);
}

/**
 * Retrieves a vector of cities that have the specified climate.
 *
 * @param map The map containing the cities and their corresponding climate information.
 * @param climate The climate to search for.
 * @return A vector of cities that have the specified climate.
 */
vector<string> getCitiesWithClimate(Map<string, CapitalAndClimate> &map, string climate)
{
    vector<string> cities;
    vector<string> keys = map.keys();
    for (string key : keys)
    {
        CapitalAndClimate value = map.get(key);
        if (value.climate == climate)
        {
            cities.push_back(value.capital);
        }
    }
    if (cities.empty())
    {
        cout << "No cities found with the specified climate.\n";
        return;
    }
    return cities;
}

int main()
{
    /* Pair<string, int> *a = new Pair<string, int>("test", 1);
    a->next = new Pair<string, int>("test2", 2); */
    string department;
    string climate;
    Map<string, CapitalAndClimate> map(10);
    map["Amazonas"] = {"Leticia", "Tropical"};
    map["Antioquia"] = {"Medellín", "Temperate"};
    map["Arauca"] = {"Arauca", "Tropical"};
    map["Atlántico"] = {"Barranquilla", "Tropical"};
    map["Bolívar"] = {"Cartagena", "Tropical"};
    map["Boyacá"] = {"Tunja", "Temperate"};
    map["Caldas"] = {"Manizales", "Temperate"};
    map["Caquetá"] = {"Florencia", "Tropical"};
    map["Casanare"] = {"Yopal", "Tropical"};
    map["Cauca"] = {"Popayán", "Temperate"};

    vector<string> departamentos = map.keys();
    vector<CapitalAndClimate> climas = map.values();
    for (string departamento : departamentos)
    {
        cout << "- " << departamento << endl;
    }
    cout << "Ingrese un departamento: ";
    cin >> department;
    CapitalAndClimate capitalAndClimate = getCapitalAndClimate(map, department);
    cout << "La capital de " << department << " es " << capitalAndClimate.capital << " y su clima es " << capitalAndClimate.climate << "." << endl;

    cout << endl;

    for (CapitalAndClimate clima : climas)
    {
        cout << "- " << clima.climate << endl;
    }
    cout << "Ingrese un clima: ";
    cin >> climate;
    vector<string> cities = getCitiesWithClimate(map, climate);
    cout << "Las ciudades con clima " << climate << " son:" << endl;
    for (string city : cities)
    {
        cout << "- " << city << endl;
    }

    return 0;
}