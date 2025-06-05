#include <string.h>       // 包含字符串处理函数的头文件，用于后续的字符串比较
#include <px4_log.h>      // 包含PX4日志记录功能的头文件，用于输出信息
extern "C" __EXPORT int test_app_main(int argc, char * argv[]); // 声明主函数，使用extern "C"来确保C++编译器以C语言的方式编译这个函数，__EXPORT用于导出函数，使其可供其他模块调用
static int is_running = 0; // 定义一个静态变量，用于表示应用程序的运行状态，初始值为0（未运行）
int start_command_base(int argc, char * argv[]) // 定义启动命令的函数
{
    is_running = 1; // 将运行状态设置为1（运行中）
    PX4_INFO("Hello Sky!"); // 输出欢迎信息到PX4日志
    for (unsigned int i = 0; i != 5; ++i) // 循环5次
    {
        PX4_INFO("%d", i); // 每次循环输出当前的计数值
    }
    return 0; // 返回0表示成功
}
int status_command() // 定义状态查询命令的函数
{
    if (is_running == 1) // 如果应用正在运行
    {
        PX4_INFO("app is running!"); // 输出应用运行中的状态信息
    }
    else // 如果应用未运行
    {
        PX4_INFO("app not running!"); // 输出应用未运行的状态信息
    }
    return 0; // 返回0表示成功
}
int stop_command() // 定义停止命令的函数
{
    is_running = 0; // 将运行状态设置为0（未运行）
    PX4_INFO("app stopped!"); // 输出应用已停止的信息
    return 0; // 返回0表示成功
}
int custom_command(int argc, char * argv[]) // 定义处理未知命令的函数
{
    PX4_ERR("unknown command!"); // 输出未知命令的错误信息
    return 0; // 返回0表示成功（这里可能应该返回一个错误码，比如-1）
}
int print_usage() // 定义打印使用说明的函数
{
    PX4_INFO("This is a test app!"); // 输出应用的简单描述作为使用说明
    return 0; // 返回0表示成功
}
int test_app_main(int argc, char * argv[]) // 定义主函数
{
    if (argc <= 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "info") == 0 || strcmp(argv[1], "usage") == 0) // 如果参数数量小于等于1，或者第一个参数是-h、help、info或usage
    {
        return print_usage(); // 调用使用说明函数并返回其结果
    }
    if (strcmp(argv[1], "start") == 0) // 如果第一个参数是start
    {
        return start_command_base(argc - 1, argv + 1); // 调用启动命令函数并返回其结果
    }
    if (strcmp(argv[1], "status") == 0) // 如果第一个参数是status
    {
        return status_command(); // 调用状态命令函数并返回其结果
    }
    if (strcmp(argv[1], "stop") == 0) // 如果第一个参数是stop
    {
        return stop_command(); // 调用停止命令函数并返回其结果
    }
    int ret = custom_command(argc - 1, argv + 1); // 对于其他未知命令，调用自定义命令函数并将结果存储在ret中
    return ret; // 返回自定义命令函数的结果
}
