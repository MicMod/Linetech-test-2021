// Task 1
#include <iostream> 
#include <thread> 
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm> 

void calc_average(std::vector<float> vec, float *average) 
{   
    *average = std::accumulate( vec.begin(), vec.end(), 0.0)/ vec.size();
}

void calc_median(std::vector<float> vec, float *median)
{   
    size_t size = vec.size();

    std::sort(vec.begin(), vec.end()); 

    if (size % 2 == 0)
    {
        *median = (vec[size / 2 - 1] + vec[size / 2]) / 2;
    }
    else 
    {
       *median = vec[size / 2];
    }
}

void read_data(std::string fileName, std::vector<float> & vec)
{  
    std::ifstream in(fileName.c_str());

    if(!in){
        std::cout <<"Unable to open file: " <<fileName <<std::endl;
        exit(1);
    }

    float x;
    while(in >> x){
        vec.push_back(x);
    }
    in.close();


}

void print_results(float average, float median)
{
    if (average == median)
    {
        std::cout<<"The average equals to the median"<<std::endl; 
    }
    else{
        if(average>median)
        {
            std::cout<<"The average is greater than the median"<<std::endl; 
        }
        else
        {
            std::cout<<"The median is greater than the average"<<std::endl; 
        }
    }

    std::cout<<"Average: "<<average<<std::endl;
    std::cout<<"Median: "<<median<<std::endl;
}

int main() 
{   
    std::vector<float> data;
    float average;
    float median;

    read_data("1/data.txt", data);
    
    std::thread first (calc_average, data, &average); //  first thread that calculate avreage
    std::thread second (calc_median, data, &median); // second thread that calculate median

    // synchronize threads:
    first.join();             
    second.join();    

    print_results(average, median);


  return 0;
}