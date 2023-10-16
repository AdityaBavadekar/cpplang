import os
import subprocess
import time

program_name = "main"

dirs = os.listdir('.')
cpp_files = [f for f in dirs if os.path.isfile('.\\'+f) and f.endswith('.cpp')]
dirs = [f for f in dirs if os.path.isdir('.\\'+f)]
for fdir in dirs:
    files = ['.\\'+fdir+'\\'+f for f in os.listdir('.\\' + fdir) if f.endswith('.cpp')]
    cpp_files += files

command = "g++ -g " + ' '.join(cpp_files) + " -o " + program_name
print('Exec : "',command,'"\n')
start = time.time()
result_code = os.system(command)
end = time.time()
if result_code == 0:
    print("Successfully Compiled.")

else:
    print("Compilation Failed!")
print(f"Execution time : {end-start} sec")
print('\a')