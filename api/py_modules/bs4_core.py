from bs4 import BeautifulSoup
import re

html_content = '''
<html>
    <head><title>Test Page</title></head>
    <body>
        <h1>Welcome to Example Page</h1>
        <p class='dd'>This is a paragraph with the word Example.</p>
        <p>Another paragraph with example in lowercase.</p>
        <a href="#" class='ff'>This is a link with Example in it.</a>
        <h1 class='ss' id='ssa'> rsioex@gmail.com</h1>
    </body>
</html>
'''



def find_email(soup):
    emails = re.findall(r'[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}', soup.get_text())
    if emails:
        print("Emails found:")
        for email in set(emails):
            print(email)

    else: print("No emails found.")



def search_string(soup:BeautifulSoup,query:str):

    matches = soup.find_all(string=re.compile(query, re.IGNORECASE))

    if matches:
        print("Found matches:")
        for match in matches:
            print(match.strip())
    else:
        print(f"No matches found for '{search_string}'.")


def find_all_attr(soup:BeautifulSoup,el):
    p = soup.find(el)
    return p.attrs




def match_string(soup:BeautifulSoup,el:str):
    matches = soup.find_all(string=re.compile(el))

    i = 1
    if matches:
        for match in matches:
            parent_element = match.find_parent()  # Get the parent HTML element of the match
            print(f"\n[{i}] found text : '{match.strip()}'")
            print(f"{parent_element.prettify()}\n")
            i = i + 1
    else:
        print(f"No matches found for '{search_string}'.")

