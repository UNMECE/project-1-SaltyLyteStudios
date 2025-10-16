#include <iostream>
#include "capacitor.h"
#include <cmath>

//assumes that capacitor is already initialized with values
Capacitor* ChargeCapacitorForTime(Capacitor* capacitor, double resistance, int  timesteps, double t_0, double DeltaT)
{

    std::cout << "Capacitance: " << (*capacitor).C<< std::endl;

    for (int i = 1; i < timesteps; i++)
    {
        //V(t+1) = V(t) + I(t) \Delta t  \frac{1}{C} 
        capacitor[0].voltage[i] = capacitor[0].voltage[i-1] + capacitor[0].current[i-1] * 1/(capacitor[0].C)*DeltaT;
        capacitor[0].current[i] = capacitor[0].current[i-1] - (capacitor[0].current[i]/(resistance*capacitor[0].C))*DeltaT;

        if (i%200 == 0)
        {
            std::cout<< "voltage: "<<capacitor[0].voltage[i] << " | ";
            std::cout<< "current: "<<capacitor[0].current[i]<<std::endl;
        }
        

    }
    
    return capacitor;
}

Capacitor* InitCapacitorForTime(double time, double voltage, double current, double capacitance,int timesteps)
{
    Capacitor* capacitor_ptr = (Capacitor*)malloc(sizeof(Capacitor));
    (*capacitor_ptr).time = (double*)malloc(sizeof(double)*timesteps);
    (*capacitor_ptr).voltage = (double*)malloc(sizeof(double)*timesteps);
    (*capacitor_ptr).current = (double*)malloc(sizeof(double)*timesteps);

    for (int i = 0; i < timesteps; i++)
    {
        (*capacitor_ptr).time[i] = time;
        (*capacitor_ptr).voltage[i] = voltage;
        (*capacitor_ptr).current[i] = current;
    }
    
    (*capacitor_ptr).C = capacitance;

    std::cout<< "number of timesteps: " << timesteps << std::endl;
    std::cout<< "capacitance: " << capacitor_ptr[0].C << std::endl;
    std::cout<< "current: " << capacitor_ptr[0].current[0] << std::endl;
    std::cout<< "voltage at time 0: " << capacitor_ptr[0].voltage[0] << std::endl;

    return capacitor_ptr;
}

void DestroyCapacitor(Capacitor* capacitor_ptr)
{
    free(capacitor_ptr[0].voltage);
    free(capacitor_ptr[0].current);
    free(capacitor_ptr[0].time);
    free(capacitor_ptr);
}

int main ()
{

    const double Dt = 1*(pow(10, -10));
    const double final_time = 5*(pow(10,-6));
    const double number_of_timesteps = 50000;
    const double R = 1;
    const double C = 100*(pow(10,-12));
    const double I = 1*(pow(10,-2));
    const double V_0 =  10.0;
    const double t_0 = 0;

    Capacitor* capacitor_ptr = InitCapacitorForTime(t_0,V_0,I,C,number_of_timesteps);

    capacitor_ptr = ChargeCapacitorForTime(capacitor_ptr, R, number_of_timesteps, t_0, Dt);

    return 0;
}