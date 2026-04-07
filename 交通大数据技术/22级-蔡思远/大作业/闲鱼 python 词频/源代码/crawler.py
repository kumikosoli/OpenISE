import requests
from bs4 import BeautifulSoup

def crawl_and_save(url):
    # 发送 HTTP 请求获取网页内容
    response = requests.get(url)

    # 检查请求是否成功
    if response.status_code == 200:
        # 解析网页内容
        soup = BeautifulSoup(response.text, 'html.parser')

        # 提取文字内容
        text = soup.get_text()

        # 存储到 txt 文件
        with open('a.txt', 'w', encoding='utf-8') as file:
            file.write(text)
    else:
        print(f"请求失败，状态码: {response.status_code}")


crawl_and_save("https://novel.tingroom.com/html/book/show/42/1235.html")
