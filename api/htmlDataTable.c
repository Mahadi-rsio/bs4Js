#include <python3.12/Python.h>
#include <stdio.h>
#include <stdlib.h>

static PyObject* html_data_table(PyObject* self, PyObject* args) {
    PyObject* soup;
    if (!PyArg_ParseTuple(args, "O", &soup)) {
        return NULL;
    }

    const char* tags[] = {
        "html", "head", "body", "title", "meta", "link", "script", "style",
        "h1", "h2", "h3", "h4", "h5", "h6", "p", "a", "img", "div",
        "span", "ul", "ol", "li", "table", "tr", "td", "th", "form",
        "input", "textarea", "button", "label", "select", "option", "br",
        "hr", "header", "footer", "nav", "article", "section", "aside",
        "main", "pre", "code", "iframe", "canvas", "svg"
    };

    size_t tag_count[sizeof(tags) / sizeof(tags[0])] = {0};
    PyObject* find_all_method = PyObject_GetAttrString(soup, "find_all");
    if (!find_all_method) {
        PyErr_SetString(PyExc_AttributeError, "Soup object does not have method 'find_all'");
        return NULL;
    }

    for (size_t i = 0; i < sizeof(tags) / sizeof(tags[0]); i++) {
        PyObject* tag_name = PyUnicode_FromString(tags[i]);
        PyObject* tag_list = PyObject_CallFunctionObjArgs(find_all_method, tag_name, NULL);
        Py_DECREF(tag_name);

        if (!tag_list) {
            Py_DECREF(find_all_method);
            return NULL;
        }

        tag_count[i] = PyObject_Length(tag_list);
        Py_DECREF(tag_list);
    }

    Py_DECREF(find_all_method);

    int column_width = 60;
    for (size_t i = 0; i < sizeof(tags) / sizeof(tags[0]); i += 5) {
        for (size_t j = 0; j < 5; j++) {
            size_t index = i + j;
            if (index < sizeof(tags) / sizeof(tags[0])) {
                // Allocate memory for buffers dynamically
                char* tag_colored = malloc(256);
                char* arrow_colored = malloc(50);
                char* count_colored = malloc(256);

                snprintf(tag_colored, 256, "\033[38;2;%d;%d;%dm<%s>\033[0m",
                         tag_count[index] > 0 ? 255 : 255,
                         tag_count[index] > 0 ? 255 : 100,
                         tag_count[index] > 0 ? 160 : 100,
                         tags[index]);

                snprintf(arrow_colored, 50, "\033[38;2;255;200;80m-->\033[0m");

                snprintf(count_colored, 256, "\033[38;2;%d;%d;%dm%zu\033[0m",
                         tag_count[index] > 0 ? 155 : 255,
                         tag_count[index] > 0 ? 250 : 50,
                         tag_count[index] > 0 ? 130 : 50,
                         tag_count[index]);

                printf("%-*s %s %s ", column_width, tag_colored, arrow_colored, count_colored);

                // Free allocated memory
                free(tag_colored);
                free(arrow_colored);
                free(count_colored);
            }
        }
        printf("\n");
    }

    Py_RETURN_NONE;
}
