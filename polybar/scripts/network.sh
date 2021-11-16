#! /bin/python

import re
import subprocess
import sys

def parse_freq(s: str) -> (str, str):
	pattern = re.compile("(.*)e\+(.*)")
	result = pattern.match(s)
	return (result.group(1), result.group(2))

def get_magnitude(power: int) -> str:
	if power < 3:
		return ""
	elif power < 6:
		return "k"
	elif power < 9:
		return "M"
	elif power < 12:
		return "G"
	else:
		return "x"

def print_information(name: str, freq: float, mag: str) -> None:
	print(" {} ({} {}Hz)".format(name, freq, mag))
	return

def main() -> None:
	network_name_process = subprocess.run(["iwgetid", "--raw"], capture_output=True)
	freq_process = subprocess.run(["iwgetid", "--freq", "--raw"], capture_output=True)
	
	raw_network_name = network_name_process.stdout
	raw_freq = freq_process.stdout

	if (network_name_process.returncode or freq_process.returncode):
		print(" Not Connected")
		return
	else:
		print("")
		return

	network_name = raw_network_name.decode("utf-8").strip()
	freq_info = raw_freq.decode("utf-8").strip()

	parsed_freq = parse_freq(freq_info)
	
	freq_power = float(parsed_freq[1])
	freq_num = float(parsed_freq[0]) * (10 ** (freq_power % 3))
	freq_mag = get_magnitude(freq_power)

	# print(freq_info, parsed_freq, freq_power, freq_num, freq_mag)

	print_information(network_name, str(freq_num), freq_mag)
	return

if __name__ == "__main__":
	main()
