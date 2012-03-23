# *-* coding:utf-8 *-*

# ���ļ�
dcic32 = open("dcic32.h", "r")
outfile = open("out.txt", "w")

# ��ȡ�ļ���������
all_lines = dcic32.readlines()

# �����ļ���, ȡ������API����
filtered_lines = []
for line in all_lines:
	if line.find("__stdcall") != -1 or line.find("__int16") != -1:
		filtered_lines.append(line)

# typedef �������к��� func_type_
for line in filtered_lines:
	line.strip() # ȥ��ǰ��ո�
	function_name = line[line.find("__stdcall") + len("__stdcall"):line.find("(")].strip()
	head_str = line[:line.find("__stdcall")].strip() # ��HANDLE����__int16
	outfile.write("typedef %s(__stdcall *func_type_%s)%s" % (head_str, function_name, line[line.find("("):]))

# ����
outfile.write("\n\n")

# �������еĺ������� func_type_��my��Ӧ�ķ�ʽ
function_names = {}

# typedef �������к��� my
for line in filtered_lines:
	line.strip() # ȥ��ǰ��ո�
	function_name = line[line.find("__stdcall") + len("__stdcall"):line.find("(")].strip()
	# �»��ߺ����ĸ��д
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
	head_str = line[:line.find("__stdcall")].strip() # ��HANDLE����__int16
	outfile.write("typedef %s(__stdcall *%s)%s" % (head_str, new_function_name, line[line.find("("):]))
# ����
outfile.write("\n\n")

for k in function_names.keys():
	outfile.write(k + " " + function_names[k] + ";\n")
# ����
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write(function_names[k] + " my_" + k[10:] + ";\n")
# ����
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write("\t" + function_names[k] + " = NULL;\n")
# ����
outfile.write("\n\n")
for k in function_names.keys():
	outfile.write("\t%s = (%s)GetProcAddress(hinstLib, \"%s\");\n" % (" my_" + k[10:], function_names[k], k[10:]))

dcic32.close()
outfile.close()