from urllib import request
from bs4 import BeautifulSoup

content = request.urlopen("http://www.kma.go.kr/weather/forecast/mid-term-rss3.jsp?stnId=108")
soup = BeautifulSoup(content, 'html.parser')

print(soup.select("data"))