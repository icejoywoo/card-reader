# -.- coding:utf-8 -.-
import os
import random
import threading
import time

class ReaderTest(threading.Thread):
	def run(self):
		for _ in xrange(1000):
			readerId = random.randint(1,4)
			print "reader id:", readerId
			# ����ǰ��������ļ�, һ�����ʱ�Ĳ���, ����Ƚ��ȶ�, �ļ�ֻ������һ��, �������ֻ��Ϊ�˿��������ļ����ȶ���
			cmd = "downloadFile\CardReaderClientDllTest.exe " + str(readerId)
			os.system(cmd)
			time.sleep(0.1)

if __name__ == "__main__":
	ReaderTest().start()
	ReaderTest().start()
	ReaderTest().start()
	ReaderTest().start()