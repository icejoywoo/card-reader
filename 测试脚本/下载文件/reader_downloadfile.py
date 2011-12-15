# -.- coding:utf-8 -.-
import os
import random
import threading
import time

class ReaderTest(threading.Thread):
	def run(self):
		for readerId in range(1, 5):
			print "reader id:", readerId
			# 这个是包含下载文件, 一个最耗时的操作, 总体比较稳定, 文件只需下载一次, 这个测试只是为了看看下载文件的稳定性
			cmd = "CardReaderClientDllTest.exe " + str(readerId)
			for line in os.popen(cmd).readlines():
				print line
			time.sleep(0.1)

if __name__ == "__main__":
	ReaderTest().start()