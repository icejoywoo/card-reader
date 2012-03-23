# *-* coding:utf-8 *-*

# 打开文件
dcic32 = open("dcic32.h", "r")
outfile = open("out.txt", "w")

# 读取文件的所有行
all_lines = dcic32.readlines()

# 过滤文件行, 取得所有API函数
filtered_lines = []
for line in all_lines:
	if line.find("__stdcall") != -1 or line.find("__int16") != -1:
		filtered_lines.append(line)

# typedef 定义所有函数 func_type_
for line in filtered_lines:
	line.strip() # 去掉前后空格
	function_name = line[line.find("__stdcall") + len("__stdcall"):line.find("(")].strip()
	head_str = line[:line.find("__stdcall")].strip() # 是HANDLE还是__int16
	outfile.write("typedef %s(__stdcall *func_type_%s)%s" % (head_str, function_name, line[line.find("("):]))

# 换行
outfile.write("\n\n")

# 保存所有的函数名称 func_type_和my对应的方式
function_names = {}

# typedef 定义所有函数 my
for line in filtered_lines:
	line.strip() # 去掉前后空格
	function_name = line[line.find("__stdcall") + len("__stdcall"):line.find("(")].strip()
	# 下划线后的字母大写
	new_function_name = "my"
	flag = False
	for c in function_name:
		if c == '_':
			flag = True
		elif flag:
			new_function_name += c.upper()
			flag = False
		else:
			new_function_name += c
	function_names["func_type_" + function_name] = new_function_name
	head_str = line[:line.find("__stdcall")].strip() # 是HANDLE还是__int16
	outfile.write("typedef %s(__stdcall *%s)%s" % (head_str, new_function_name, line[line.find("("):]))
# 换行
outfile.write("\n\n")

for k in function_names.keys():
	outfile.write(k + " " + function_names[k] + ";\n")
# 换行
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write(function_names[k] + " my_" + k[10:] + ";\n")
# 换行
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write("\t" + function_names[k] + " = NULL;\n")
# 换行
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write("\t%s = (%s)GetProcAddress(hinstLib, \"%s\");\n" % (" my_" + k[10:], function_names[k], k[10:]))

dcic32.close()
outfile.close()