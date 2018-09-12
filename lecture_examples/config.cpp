#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/parser.h>

using namespace std;




struct pose
{
    double x,y,t;
    void Print(const string &name = "")
    {
        cout << name << ": x: " << x <<", y: " << y << ", theta: " << t << endl;
    }

    // load from YAML
    void LoadFrom(const YAML::Node &node)
    {
        x = node["x"].as<double>();
        y = node["y"].as<double>();
        t = node["t"].as<double>();
    }
};


int main(int argc, char ** argv)
{

    string config_type= "yaml";

    if(argc > 1 && argc < 5)
        config_type = string(argv[1]);

    // declare variables
    pose start, end;
    string runID;



    if(config_type == "yaml")
    {
        YAML::Node config = YAML::LoadFile("../config.yaml");

        start.LoadFrom(config["start"]);
        end.LoadFrom(config["end"]);
        runID = config["run"].as<string>();
    }


    else if(config_type == "txt")
    {

        std::ifstream config("../config.txt", std::ios::in);

        string keyword;
        while(config >> keyword)
        {
            cout << "Current keyword: " << keyword << endl;
            //config >> value;
            if(keyword == "start")
            {
                config >> start.x;
                config >> start.y;
                config >> start.t;
            }
            else if(keyword == "end")
            {
                config >> end.x;
                config >> end.y;
                config >> end.t;
            }
            else if(keyword == "run")
                config >> runID;
        }
    }

    else if(argc > 7)
    {
        cout << "reading arguments"<< endl;
        start.x = atof(argv[1]);
        start.y = atof(argv[2]);
        start.t = atof(argv[3]);
        end.x = atof(argv[4]);
        end.y = atof(argv[5]);
        end.t = atof(argv[6]);
        runID = argv[7];
        cout << "ok reading arguments"<< endl;

    }



    // print parameters
    start.Print("start");
    end.Print("end");
    cout << "run ID: " << runID << endl;


}
