#include <iostream>
#include <cstdlib>
#include <chrono>
#include <random>
#include <vector>
#include <math.h>

struct Triple
{
    int first;
    int second;
    int third;
};


class Cache
{
    int cache_1mb[262144];
    int cache_2mb[524288];
    int cache_4mb[1048576];
    int cache_8mb[2097152];
    int cache_9mb[2359296];

public:


    int method_(short direction, short cache_size, int* cache)
    {
        for (size_t i = 0; i < cache_size*262144; ++i)
        {
            cache[i] = rand();
        }
        std::chrono::time_point<std::chrono::system_clock> start, end;

        int a;

        std::vector<int> vector_of_iterators[cache_size*262144];

        for (size_t i = 0; i < cache_size*262144; ++i)
        {
            vector_of_iterators[i] = i;
        }
    
        std::random_device rd;
        std::mt19937 g(rd());
    
        std::shuffle(vector_of_iterators.begin(), vector_of_iterators.end(), g);

        short direct = abs(direction);

        size_t i = direct*cache_size*262144;

        start = std::chrono::system_clock::now();   //START-------------------------------

        while ( i != (direct + pow((-1),direct))*cache_size*262144)
        {
            a = cache[i];
            i = i + pow((-1),direct); 
        }

        end = std::chrono::system_clock::now();     //END---------------------------------

        if (direction == -1)
        {

            start = std::chrono::system_clock::now(); //START-------------------------------
            i = 0;
            while ( i != cache_size*262144)
            {
                a = cache[vector_of_iterators[i]];
                i++;
            }
            end = std::chrono::system_clock::now(); //END---------------------------------

            int time_result = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            return time_result;

        } else
        {
            int time_result = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
            return time_result;
        }
    }

    Triple universal_experiment(short cache_size, int* cache)
    {
        double forw = 0;
        double rev = 0;
        double rand = 0;
        for (size_t i = 0; i < 1000; ++i)
        {
           rand = rand + method_(-1,cache_size,cache); //Рандом
           forw = forw + method_(0,cache_size,cache); //Прямой
           rev = rev + method_(1,cache_size,cache);  //Обратный
        }

        Triple resultat;

        resultat.first = forw/1000;
        resultat.second = rand/1000;
        resultat.third = rev/1000;

        return resultat;
    }

    Triple experiments_1mb()
    {
        Triple time;
        time = universal_experiment(262144, cache_1mb);
        return time;
    }
    Triple experiments_2mb()
    {
        Triple time;
        time = universal_experiment(524288, cache_2mb);
        return time;
    }
    Triple experiments_4mb()
    {
        Triple time;
        time = universal_experiment(1048576, cache_4mb);
        return time;
    }
    Triple experiments_8mb()
    {
        Triple time;
        time = universal_experiment(2097152, cache_8mb);        
        return time;
    }
    Triple experiments_9mb()
    {
        Triple time;
        time = universal_experiment(2359296, cache_9mb);
        return time;
    }

};

int main ()
{
    Cache caches;
    std::cout << caches.experiments_1mb().first << std::endl;
    std::cout << caches.experiments_1mb().second << std::endl;
    std::cout << caches.experiments_1mb().third << std::endl;
    std::cout << "________________________________" << std::endl << std::endl;

    std::cout << caches.experiments_2mb().first << std::endl;
    std::cout << caches.experiments_2mb().second << std::endl;
    std::cout << caches.experiments_2mb().third << std::endl;
    std::cout << "________________________________" << std::endl << std::endl;

    std::cout << caches.experiments_4mb().first << std::endl;
    std::cout << caches.experiments_4mb().second << std::endl;
    std::cout << caches.experiments_4mb().third << std::endl;
    std::cout << "________________________________" << std::endl << std::endl;

    std::cout << caches.experiments_8mb().first << std::endl;
    std::cout << caches.experiments_8mb().second << std::endl;
    std::cout << caches.experiments_8mb().third << std::endl;
    std::cout << "________________________________" << std::endl << std::endl;

    std::cout << caches.experiments_9mb().first << std::endl;
    std::cout << caches.experiments_9mb().second << std::endl;
    std::cout << caches.experiments_9mb().third << std::endl;
    std::cout << "________________________________" << std::endl << std::endl;
}