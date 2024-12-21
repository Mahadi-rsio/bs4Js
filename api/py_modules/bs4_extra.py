from bs4 import BeautifulSoup

def Html_Data_Table(soup:BeautifulSoup):
    def color_text(text, r, g, b):
        return f"\033[38;2;{r};{g};{b}m{text}\033[0m"


    tags = [
        "html", "head", "body", "title", "meta", "link", "script", "style",
        "h1", "h2", "h3", "h4", "h5", "h6", "p", "a", "img", "div", 
        "span", "ul", "ol", "li", "table", "tr", "td", "th", "form", 
        "input", "textarea", "button", "label", "select", "option", "br", 
        "hr", "header", "footer", "nav", "article", "section", "aside", 
        "main","pre", "code", "iframe", "canvas","svg"
    ]

    results = []
    for get_tag in tags:
        tag_count = (soup.find_all(get_tag)).__len__()
        results.append((get_tag, tag_count))  # Store tag name and count as a tuple

    results.sort(key=lambda x: x[1], reverse=True)

    column_width = 60  

    for i in range(0, len(results), 5):  # Group into rows of 4
        row = []
        for j in range(5):  # Process each column
            index = i + j
            if index < len(results):
                tag_name, tag_count = results[index]

                tag_colored = color_text(f'<{tag_name}>'.ljust(10), 255, 255, 160) if tag_count != 0 else color_text(f'<{tag_name}>'.ljust(10),255,100,100)  
                arrow_colored = color_text("-->", 255, 200, 80).center(2)  # Yellow
                colored_brackets = color_text(f'{tag_count}', 155, 250, 130) if tag_count != 0 else color_text('0',255,50,50)

                entry = f"  {tag_colored} {arrow_colored} {colored_brackets}".ljust(column_width)
                row.append(entry)
        print("".join(row))
