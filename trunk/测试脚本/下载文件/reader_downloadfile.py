# -.- coding:utf-8 -.-
import os
import random
import threading
import time

class ReaderTest(threading.Thread):
	def run(self):
		for readerId in range(1, 5):
			print "reader id:", readerId
			# ����ǰ��������ļ�, һ�����ʱ�Ĳ���, ����Ƚ��ȶ�, �ļ�ֻ������һ��, �������ֻ��Ϊ�˿��������ļ����ȶ���
			cmd = "CardReaderClientDllTest.exe " + str(readerId)
			for line in os.popen(cmd).readlines():
				print line
			time.sleep(0.1)

if __name__ == "__main__":
	ReaderTest().start()