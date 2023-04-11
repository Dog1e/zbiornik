#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <cmath>

using namespace std;

string date1(int days)
{
    string day;
    string month;
    string year = "2015";
    int months[6] = {30, 31, 30, 31, 31, 30};
    if(days<=30)
    {
        month = "kwiecień";
        day = to_string(days);
    }
    else if(days>30 && days<=61)
    {
        month = "maj";
        day = to_string(days-30);
    }
    else if(days>61 && days<=91)
    {
        month = "czerwiec";
        day = to_string(days-61);
    }
    else if(days>91 && days<=122)
    {
        month = "lipiec";
        day = to_string(days-91);
    }
    else if(days>122 && days<=153)
    {
        month = "sierpień";
        day = to_string(days-122);
    }
    else if(days>153 && days<=183)
    {
        month = "wrzesień";
        day = to_string(days-153);
    }
    return(day+" "+month+" "+year);
}

int main(){
    int index=0;
    string line;
    double n1;
    string n2;
    vector<double> temp, prec;
    ifstream file;
    file.open("pogoda.txt");
    while(getline(file, line))
    {
        if(index!=0)
        {
            istringstream iss(line);
            iss >> n1 >> n2;

            for(int i=0;i<n2.length();i++)
            {
                if(n2[i]==',')
                {
                    n2[i]='.';
                }
            }

            temp.push_back(n1);
            prec.push_back(stod(n2));  
        }
        index++;  
    }
    file.close();

    //wypisywanie tablic
    // for(int i=0;i<temp.size();i++)
    // {
    //     cout<<temp[i]<<"      "<<prec[i]<<endl;
    // }

    //zadanie1
    int wynik1=0;
    int wynik2=0;
    int wynik3=0;
    //a
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]<=15)
        {
            wynik1=wynik1+=1;
        }
    }

    //b
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]>15 and prec[i]<=0.6)
        {
            wynik2=wynik2+=1;
        }
    }

    //c
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i]>15 and prec[i]>0.6)
        {
            wynik3=wynik3+=1;
        }
    }
    // cout<<"Zadanie 1"<<endl;
    // cout<<"zadanie 1a: "<<wynik1<<endl;
    // cout<<"zadanie 1b: "<<wynik2<<endl;
    // cout<<"zadanie 1c: "<<wynik3<<endl;


    //zadanie2
    double tank = 25000;
    int countDay;
    int firstWaterAddDay;
    int stopFirst=0;
    double addingWater = 0;
    double monthlyWater = 0;
    double firstWaterAdding = 0;
    vector<float> monthsPrice = {0, 0, 0, 0, 0, 0};

    for(int i=0;i<temp.size();i++)
    {
        countDay++;
        if(prec[i]>0)
        {
            tank += (700 * prec[i]);
            if(tank>25000)
            {
                tank=25000;
            } 
        }
        else
        {
            tank -= ceil(0.0003 * pow(temp[i], 1.5) * tank);
            if(tank<0)
            {
                tank=0;
            }
        }

        if(temp[i]>15 && prec[i]<=0.6)
        {
            if(temp[i]<=30)
            {
                if(tank<12000)
                {
                    addingWater += 25000 - tank;
                    monthlyWater += 25000 - tank;
                    tank=25000;
                    if(firstWaterAdding==0)
                    {
                        firstWaterAddDay = countDay;
                        firstWaterAdding = addingWater;
                    }
                }
                tank = tank - 12000;
            }
            else
            {
                if(tank<24000)
                {
                    addingWater += 25000 - tank;
                    monthlyWater += 25000 - tank;
                    tank=25000;
                    if(firstWaterAdding==0)
                    {
                        firstWaterAddDay = countDay;
                        firstWaterAdding = addingWater;
                    }
                }
                tank -= 24000;
            }
        }
        
        if(i==29)
        {
            monthsPrice[0] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
        if(i==60)
        {
            monthsPrice[1] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
        if(i==90)
        {
            monthsPrice[2] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
        if(i==121)
        {
            monthsPrice[3] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
        if(i==152)
        {
            monthsPrice[4] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
        if(i==182)
        {
            monthsPrice[5] = (monthlyWater/1000)*11.74;
            monthlyWater=0;
        }
    }
    // cout<<endl<<"Zadanie 2: "<<endl;
    // cout<<"Pierwsze dolanie wody: ";
    // cout<<date1(firstWaterAddDay);
    // cout<<endl;
    // cout<<"Ilość dolanej wody: "<<firstWaterAdding;

    //zadanie 3
    // cout<<endl<<endl<<"Zadanie 3: ";
    // cout<<"Cena wody w każdym miesiącu: "<<endl;
    // cout<<"kwiecień: "<<monthsPrice[0]<<"zł"<<endl;
    // cout<<"maj: "<<monthsPrice[1]<<"zł"<<endl;
    // cout<<"czerwiec: "<<monthsPrice[2]<<"zł"<<endl;
    // cout<<"lipiec: "<<monthsPrice[3]<<"zł"<<endl;
    // cout<<"sierpień: "<<monthsPrice[4]<<"zł"<<endl;
    // cout<<"wrzesień: "<<monthsPrice[5]<<"zł"<<endl;

    // cout<<endl<<"cała dolana woda: "<<addingWater;
    // cout<<endl;

    //zadanie 5
    int days;
    int maxDays; 
    int firstDay;
    int lastDay;
    for(int i=0;i<temp.size();i++)
    {
        if(prec[i]==0)
        {
            if(temp[i]>temp[i-1])
            {
                days++;
            }
        }
        else
        {
            if(days>maxDays)
            {
                firstDay = i + 1 - days;
                lastDay = i;
                maxDays = days;
            }
            days = 0;
        }
    }

    // cout<<endl<<"Zadanie 5:"<<endl;
    // cout<<"Najdłuższy okres bezdeszczowych dni gdzie temperatura rośnie: "<<maxDays<<endl;
    // cout<<"Data okresu: ";
    // cout<<date1(firstDay);
    // cout<<" - ";
    // cout<<date1(lastDay);
    // cout<<endl;


    //zadanie 6
    double maxPrec;
    double curPrec;
    for(int i=0;i<prec.size();i++)
    {
        if(prec[i]!=0)
        {
            curPrec+=prec[i];
        }
        else
        {
            if(curPrec>maxPrec)
            {
                maxPrec=curPrec;
            }
            curPrec=0;
        }
    }

    // cout<<"Zadanie 6:"<<endl;
    // cout<<"Największy opad deszczu: "<<maxPrec<<"l/m2";

    ofstream save("wyniki4.txt");
    save<<"Zadanie 1:\n"<<"zadanie 1a: "<<wynik1<<"\nzadanie 1b: "<<wynik2<<"\nzadanie 1c: "<<wynik3<<"\n";
    save<<"\nZadanie 2: "<<"\nPierwsze dolanie wody: "<<date1(firstWaterAddDay)<<"\n"<<"Ilość dolanej wody: "<<firstWaterAdding<<"l\n";
    save<<"\nZadanie 3: "<<"Cena wody w każdym miesiącu: \n"<<"kwiecień: "<<monthsPrice[0]<<"zł\n"<<"maj: "<<round(monthsPrice[1] * 100)/100<<"zł\n"<<"czerwiec: "<<monthsPrice[2]<<"zł\n"<<"lipiec: "<<monthsPrice[3]<<"zł\n"<<"sierpień: "<<monthsPrice[4]<<"zł\n"<<"wrzesień: "<<monthsPrice[5]<<"zł\n";
    save<<"\nZadanie 5:"<<"\nNajdłuższy okres bezdeszczowych dni gdzie temperatura rośnie: "<<maxDays<<" dni"<<"\nData okresu: "<<date1(firstDay)<<" - "<<date1(lastDay)<<"\n";
    save<<"\nZadanie 6:\n"<<"Największy opad deszczu: "<<maxPrec<<"l/m2";
    save.close();
    return 0;
}