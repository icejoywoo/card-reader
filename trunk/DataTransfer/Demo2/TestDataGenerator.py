# *-* coding:utf-8 *-*

file = open("CQJRSB-200907100031-��ͨ����-ICInfo", "r")
outfile = open("CQJRSB-200907100031-��ͨ����-ICInfo-test", "w")
line = file.read()
for _ in xrange(20011):
	outfile.write(line)

outfile.flush()
outfile.close()
file.close()
