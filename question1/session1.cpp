#include "session1.h"



void task_main_entry(long task_times)
{
    long thread_times = THREAD_ROUNDS;
    if (task_times / THREAD_NUMS/(NUMBERS_S/100) < THREAD_ROUNDS)
    {
        thread_times = task_times / THREAD_NUMS / (NUMBERS_S / 100);
    }
    std::vector<std::thread> threads;

    struct task_result task_res[THREAD_NUMS];
    int i = 0;
    for (i = 0;i < THREAD_NUMS;i++)
    {
        task_res[i].thread_index = 0;
        task_res[i].status = 0;
    }

    long s_result[NUMBERS_S+1];
    long long k_result[NUMBERS_S + 1];
    for (i = 0;i < NUMBERS_S+1;i++)
    {
        s_result[i] = 0;
        k_result[i] = 0;
    }
    int j=0;
    long runned_task_times = 0;

    long long s_t = GetCurrentTimeInMillis();
    long long d_t=0;
    while (1)
    {
        for (i = 0; i < THREAD_NUMS; i++)
        {

            if (task_res[i].status == 2)
            {
                for (j = 0; j < NUMBERS_S+1; j++)
                {
                    s_result[j] += task_res[i].s_result[j];
                    k_result[j] += task_res[i].k_r[j];
                }

                task_res[i].status = 0;
                d_t = GetCurrentTimeInMillis() - s_t;
                cout << runned_task_times <<endl;
                cout << " time: " << d_t << " ms. rate: " << runned_task_times/d_t << "k/s"<<endl;
            }
        }

        if (task_times - runned_task_times <= 0)
        {
            for (i = 0; i < THREAD_NUMS; i++)
            {
                if (task_res[i].status != 0)
                {
                    break;
                }
            }
            if (i == THREAD_NUMS)
            {
                break;
            }
            else
            {
                continue;
            }
           
        }

        

        for (i = 0;i < THREAD_NUMS;i++)
        {
            if (task_res[i].status == 0)
            {
                task_res[i].status = 1;
                task_res[i].r_times = thread_times;
                threads.emplace_back(ThreadFunction, &task_res[i]);
                cout << " start thread " << i << " rounds: " << task_res[i].r_times<<endl;
                runned_task_times += thread_times;
                break;
            }

        }
    }
    cout << " scheduler over"<<endl;
    for (auto& t : threads) {
        t.join();
    }
    cout << " all over" << endl;

    float r_max = 0.0f, k_max = 0.0f;
    float k_min = (float)k_result[1] / task_times;
    int r_max_i = 0, k_max_i = 0,k_min_i=1;
    for (i = 1; i < NUMBERS_S+1; i++)
    {
        if (r_max < (float)s_result[i] * 100 / task_times)
        {
            r_max = (float)s_result[i] * 100 / task_times;
            r_max_i = i;
        }
        if (k_max <  (float)k_result[i] / task_times)
        {
            k_max = (float)k_result[i] / task_times;
            k_max_i = i;
        }
        if (k_min > (float)k_result[i] / task_times)
        {
            k_min = (float)k_result[i] / task_times;
            k_min_i = i;

        }
        cout << i << " " << (float)s_result[i] * 100 / task_times << " %    " << (float)k_result[i] / task_times << endl;
    }
    cout << endl;
    cout << "存活次数最多: " << r_max_i << " , 存活 " << s_result[r_max_i] << "比例： " << r_max << " %" << endl;
    cout << "平均存活轮数最多: " << k_max_i << " , 平均存活 " << k_max << endl;
    cout << "平均存活轮数最少: " << k_min_i << " , 平均存活 " << k_min << endl;
    //cout << "max: [ " << r_max_i<<" ] " << r_max << " min: [ "<<k_min_i<<" ] " << k_max << endl;
}

void task_main_entry_a(long task_times)
{
    long thread_times = THREAD_ROUNDS;
    if (task_times / THREAD_NUMS < THREAD_ROUNDS)
    {
        thread_times = task_times / THREAD_NUMS;
    }
   

    std::vector<std::thread> threads;

    struct task_result task_res[THREAD_NUMS];
    int i = 0;
    for (i = 0;i < THREAD_NUMS;i++)
    {
        task_res[i].thread_index = 0;
        task_res[i].status = 0;
    }

    long s_result[101];
    long k_result[101];
    for (i = 0;i < 101;i++)
    {
        s_result[i] = 0;
    }
    int j = 0;
    int k=0;
    long runned_task_times = 0;

    long long s_t = GetCurrentTimeInMillis();
    long long d_t = 0;
    bool is_s=false;
    while (1)
    {
        for (i = 0; i < THREAD_NUMS; i++)
        {

            if (task_res[i].status == 2)
            {
                for (j = 0; j < 101; j++)
                {
                    s_result[j] += task_res[i].s_result[j];
                    k_result[j] += task_res[i].k_r[j];
                }

                task_res[i].status = 0;
                d_t = GetCurrentTimeInMillis() - s_t;
                is_s = true;
                for (k = 1; k < 100; k++)
                {
                    if(s_result[k]>s_result[k+1])
                    {
                        is_s = false;
                        cout << " false k= " << k << " " << s_result[k] << " "<<s_result[k+1]<<endl;
                        break;
                    }
                }
                if (is_s)
                {
                    cout << "1 " << runned_task_times << endl;
                }
                else
                {
                    cout << "0 " << runned_task_times << endl;
                }

               
                //cout << " time: " << d_t << " ms. rate: " << runned_task_times / d_t << "/ms" << endl;
            }
        }

        if (task_times - runned_task_times <= 0)
        {
            for (i = 0; i < THREAD_NUMS; i++)
            {
                if (task_res[i].status != 0)
                {
                    break;
                }
            }
            if (i == THREAD_NUMS)
            {
                break;
            }
            else
            {
                continue;
            }

        }



        for (i = 0;i < THREAD_NUMS;i++)
        {
            if (task_res[i].status == 0)
            {
                task_res[i].status = 1;
                task_res[i].r_times = thread_times;
                threads.emplace_back(ThreadFunction, &task_res[i]);
                // cout << " start thread " << i << " rounds: " << task_res[i].r_times<<endl;
                runned_task_times += thread_times;
                break;
            }

        }
    }
    d_t = GetCurrentTimeInMillis() - s_t;
    
    for (auto& t : threads) {
        t.join();
    }
   

   
   
}

DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
    struct task_result* task_r = (struct task_result*)lpParam;

    // initial 
    long i = 0;
    int j = 0;
    for (i = 0; i < NUMBERS_S+1; i++)
    {
        task_r->s_result[i] = 0;
        task_r->k_r[i]=0;
    }


    for (i = 0;i < task_r->r_times;i++)
    {
        //task_r->s_result[run_once_s()]++;
        task_r->s_result[run_once_s(task_r)]++;
    }

    task_r->status = 2;

    return 0;
}
int run_once_s()
{
    // gen random
    int i = 0;
    int j = 0;
    int rand_number;
    int queue_s[NUMBERS_S];
    for (i = 0; i < NUMBERS_S; i++)
    {
        queue_s[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (i = 0; i < NUMBERS_S-1; i++)
    {
        std::uniform_int_distribution<> dis(1, (NUMBERS_S+1 - i) / 2);
        rand_number = (dis(gen) - 1) * 2;

        queue_s[rand_number] = 0;
        for (j = rand_number; j < NUMBERS_S -1- i; j++)
        {
            queue_s[j] = queue_s[j + 1];
        }
    }
    return queue_s[0];
}
int run_once_s(struct task_result* task_re)
{
    // gen random
    int i = 0;
    int j = 0;
    int rand_number;
    int queue_s[NUMBERS_S];
    for (i = 0; i < NUMBERS_S; i++)
    {
        queue_s[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    for (i = 0; i < NUMBERS_S - 1; i++)
    {
        std::uniform_int_distribution<> dis(1, (NUMBERS_S + 1 - i) / 2);
        rand_number = (dis(gen) - 1) * 2;

        task_re->k_r[queue_s[rand_number]]+=(i+1);
        queue_s[rand_number] = 0;
        for (j = rand_number; j < NUMBERS_S - 1 - i; j++)
        {
            queue_s[j] = queue_s[j + 1];
        }
    }
    task_re->k_r[queue_s[0]] += NUMBERS_S;
    return queue_s[0];
}

long long GetCurrentTimeInMillis() {

    LARGE_INTEGER frequency;

    LARGE_INTEGER counter;

    QueryPerformanceFrequency(&frequency);


    QueryPerformanceCounter(&counter);

    return (counter.QuadPart * 1000LL) / frequency.QuadPart;

}