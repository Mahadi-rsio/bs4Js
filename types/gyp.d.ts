declare module "bs4Js" {
  export function BeautifulSoup(): {
    /**
     * Initializes the BeautifulSoup parser with the given HTML string.
     * @param html - The HTML string to be parsed.
     */
    InitBs4(html: string): void;

    /**
     * Prettifies the parsed HTML, returning a formatted string.
     * @returns The prettified HTML string.
     */
    Prettify(): string;

    /**
     * Extracts all table elements from the parsed HTML.
     * @returns An array of table strings or objects (based on your implementation).
     */
    Table(): Array<string | object>;
  };
}
