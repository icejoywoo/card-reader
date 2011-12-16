# -.- coding:utf-8 -.-
import os
import random
import threading
import time

class ReaderTest(threading.Thread):
	def run(self):
		for _ in xrange(100):
			readerId = random.randint(1,6)
			print "reader id:", readerId
			# 这个是只运行一条简单的apdu命令
			cmd = "CardReaderClientDllTest.exe " + str(readerId)
			for line in os.popen(cmd).readlines():
				print line
			time.sleep(0.1)

if __name__ == "__main__":
	for _ in xrange(10):
		ReaderTest().start()