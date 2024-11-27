#pragma once
#include <iostream>
#include <random>
#include <Windows.h>
#include <thread>
#include <vector>

using namespace std;
#define THREAD_NUMS 8
#define THREAD_ROUNDS 100 * 1000
#define NUMBERS_S 600
static int thread_status[THREAD_NUMS];

struct session_result {
	long task_times = 0;
	long long task_time_sum = 0;
	long rate = 0;
	long s_result[NUMBERS_S+1];
	bool is_sorted=false;
	long k_r=0;
};

struct task_result {
	int thread_index = 0;
	long r_times = 0;
	long s_result[NUMBERS_S+1];
	long long task_time_sum = 0;
	int status = 0;
	long k_r[NUMBERS_S + 1];
};

void task_main_entry(long task_times);
void task_main_entry_a(long task_times);

DWORD WINAPI ThreadFunction(LPVOID lpParam);
int run_once_s();
int run_once_s(struct task_result * task_re);

long long GetCurrentTimeInMillis();