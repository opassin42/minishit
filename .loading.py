
import time
import sys
import glob

def ft_progress(lst):
	'''
	Progress bar for Makefile
	'''
	start_time = time.time()
	bar_size = 30
	for i in range(len(lst)):
		ratio = (i + 1) * 100 / len(lst)
		elapsed_time = time.time() - start_time
		eta = elapsed_time / ratio * 100 - elapsed_time 
		bar = ("█" * int(ratio / 100 * bar_size))
		if ratio != 100:
			color = "\033[1;31m"
		else:
			color = "\033[1;32m"
		datas = (eta, color, ratio, color, bar.ljust(bar_size, ' '), color ,i + 1, len(lst),elapsed_time)
		print("\rETA: %.2fs [%s%3d%%\033[m] [%s%s\033[m] Files:%s%d/%d\033[m | elapsed time %.2fs" % datas, end ="")
		yield i

if __name__ == "__main__":
	listy = glob.glob("srcs/*/*.c")
	listy2 = glob.glob("utils/*.c")
	file_c = listy + listy2
	for elem in ft_progress(file_c):
		time.sleep(0.05)
	print()
