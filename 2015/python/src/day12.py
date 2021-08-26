from json import loads

def jsonSum(json):
	if isinstance(json, list):
		return sum([jsonSum(x) for x in json])
	elif isinstance(json, dict):
		if "red" not in json.values():
			return sum([jsonSum(x) for x in json.values()])
		else:
			# print(json.values())
			return 0
	else:
		return sum(readNums(str(json)))


from utils.aocUtils import readNums
def main(input:str) -> tuple:
	return (sum(readNums(input)), jsonSum(loads(input)))