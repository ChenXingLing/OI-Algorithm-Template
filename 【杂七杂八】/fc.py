import os
import sys
import shutil
import time

cpp_name="tree"
test_opt=int(10)
test_name=""
# test_name=cpp_name # 测试数据名称与程序相同

# result=open("result.txt","w")
os.system("g++ "+cpp_name+".cpp -o runner") # 编译程序

for opt in range(1,test_opt+1):
    cpp_in=cpp_name+".in" # 程序读入文件
    cpp_out=cpp_name+".out" # 程序输出文件
    std_in=test_name+str(opt)+".in" # 标准读入文件
    std_out=test_name+str(opt)+".out" # 标准输出文件
    
    path=shutil.copy(std_in,cpp_in) # 将测试数据拷贝到程序读入文件
    start=time.time()
    os.system("./runner")
    end=time.time()
    runtime='%.2f'%(end-start)
    if(os.system("diff "+cpp_out+" "+std_out+" -b")):
        print(" 测试点"+str(opt)+": "+"WrongAnswer"+" (time: "+str(runtime)+"s)")
    else:
        #print(" 测试点"+str(opt)+": "+"Accepted"+" (time: "+str(runtime)+"s)")
        print(" 测试点"+str(opt)+": "+"Accepted"+" (time: "+str(runtime)+"s)")

# result.close()
cpp_in=cpp_name+".in" # 程序读入文件
cpp_out=cpp_name+".out" # 程序输出文件
std_in=test_name+str(1)+".in" # 标准读入文件
std_out=test_name+str(1)+".out" # 标准输出文件
path=shutil.copy(std_in,cpp_in) # 复原cpp_in
path=shutil.copy(std_out,cpp_out) # 复原cpp_out
