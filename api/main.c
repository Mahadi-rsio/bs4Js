#include <node/js_native_api.h>
#include <node/js_native_api_types.h>
#include <node/node_api.h>
#include <python3.12/Python.h>
#include <python3.12/abstract.h>
#include <python3.12/import.h>
#include <python3.12/object.h>
#include <python3.12/pylifecycle.h>
#include <python3.12/pythonrun.h>
#include <python3.12/tupleobject.h>
#include <python3.12/unicodeobject.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

static PyObject *BeautifulSoup_Object = NULL;
static int python_initialized = 0;


// Initialize Python Interpreter
static int py_initialize() {
    if (!python_initialized) {
        Py_Initialize();
        python_initialized = Py_IsInitialized();
    }
    return python_initialized;
}

//@@Function for Initializing BeautifulSoup Object --@param(string : Html_content)
static napi_value Init_BeautifulSoup(napi_env env, napi_callback_info info) {
    napi_value result;
    size_t argc = 1;
    napi_value argv[1];
    size_t str_len, buffer_len;

    napi_get_undefined(env, &result);

    napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    if (argc < 1) {
        fprintf(stderr, "Init_BeautifulSoup requires an HTML string as an argument\n");
        return result;
    }

    napi_get_value_string_utf8(env, argv[0], NULL, 0, &str_len);

    char *str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        fprintf(stderr, "Failed to allocate memory for HTML string\n");
        return result;
    }

    napi_get_value_string_utf8(env, argv[0], str, str_len + 1, &buffer_len);


    if (!py_initialize()) {
        fprintf(stderr, "Failed to initialize Python\n");
        free(str);
        return result;
    }

    // Initialize BeautifulSoup if not already done
    if (BeautifulSoup_Object == NULL) {
        PyObject *bs4_module = PyImport_ImportModule("bs4");
        if (!bs4_module) {
            PyErr_Print();
            free(str);
            return result;
        }

        PyObject *BeautifulSoup_class = PyObject_GetAttrString(bs4_module, "BeautifulSoup");
        Py_DECREF(bs4_module);
        if (!BeautifulSoup_class) {
            PyErr_Print();
            free(str);
            return result;
        }

        // Create arguments for BeautifulSoup
        PyObject *args = PyTuple_Pack(2, PyUnicode_FromString(str), PyUnicode_FromString("lxml"));
        free(str); // Free the C string after creating the Python object
        if (!args) {
            PyErr_Print();
            Py_DECREF(BeautifulSoup_class);
            return result;
        }

        BeautifulSoup_Object = PyObject_CallObject(BeautifulSoup_class, args);
        Py_DECREF(args);
        Py_DECREF(BeautifulSoup_class);

        if (!BeautifulSoup_Object) {
            PyErr_Print();
            return result;
        }
    }
    return result;
}

//@@Function for return HTML Title --@param(void);
static napi_value GetTitle(napi_env env, napi_callback_info info) {

    napi_value result;
    napi_get_undefined(env, &result);

    if (!BeautifulSoup_Object) {
        fprintf(stderr, "BeautifulSoup not initialized\n");
        return result;
    }

    PyObject *title_element = PyObject_CallMethod(BeautifulSoup_Object, "find", "(s)", "title");
    if (!title_element) {
        PyErr_Print();
        return result;
    }

    PyObject *title_text = PyObject_CallMethod(title_element, "get_text", NULL);
    Py_DECREF(title_element);
    if (!title_text) {
        PyErr_Print();
        return result;
    }

    const char *title_cstr = PyUnicode_AsUTF8(title_text);
    Py_DECREF(title_text);

    if (title_cstr) {
        napi_create_string_utf8(env, title_cstr, NAPI_AUTO_LENGTH, &result);
    } else {
        fprintf(stderr, "Failed to convert title to UTF-8\n");
    }

    return result;
}

//@@Function for prettify content --@param(void)
static napi_value GetPrettify(napi_env env,napi_callback_info info){
    napi_value __prettify_string;

    if (BeautifulSoup_Object==NULL) {
        PyErr_Print();
    }

    PyObject * __get_string = PyObject_CallMethodNoArgs(BeautifulSoup_Object, PyUnicode_FromString("prettify"));

    if (__get_string==NULL) {
        PyErr_Print();
    }

    char * __prettify_string_buffer = (char*) PyUnicode_AsUTF8(__get_string);

    Py_DECREF(__get_string);
    
    napi_create_string_utf8(env, __prettify_string_buffer, NAPI_AUTO_LENGTH, &__prettify_string);
    return __prettify_string;
}


static napi_value Html_Table(napi_env env,napi_callback_info info ){
    napi_value res;

    napi_get_cb_info(env, info,NULL, NULL, NULL,NULL);

    fprintf(stdout, "\n<-- Showing Html Element Table -->\n\n");

    napi_get_undefined(env,&res);

    if (BeautifulSoup_Object==NULL) {
        fprintf(stdout, "bs4 not initialized");

    }

    PyObject * sys = PyImport_ImportModule("sys");
    PyObject * path = PyObject_GetAttrString(sys, "path");

    PyList_Append(path, PyUnicode_FromString("api/py_modules"));

    Py_DECREF(path);
    Py_DECREF(sys);
    
    PyObject * __bs4_main = PyImport_ImportModule("bs4_extra");

    if (__bs4_main==NULL) {
        PyErr_Print();
        fprintf(stderr, "__bs4_main not importd");
    }

    PyObject * Table = PyObject_GetAttrString(__bs4_main, "Html_Data_Table");

    if (PyCallable_Check(Table)) {    
        PyObject * args = PyTuple_Pack(1,BeautifulSoup_Object);

        PyObject * OUT = PyObject_CallObject(Table, args) ;

        if (OUT==NULL) {
            fprintf(stdout, "Function return NULL\n");
        }

    }else {
        PyErr_Print();
        fprintf(stderr, "Function not found\n");
    }

    return res;
}

static napi_value Email(napi_env env,napi_callback_info info){
    napi_value __get_email;

    return __get_email;
}


static napi_value CreateBS4Object(napi_env env, napi_callback_info info) {
    napi_value bs4_object, init_bs4, get_title,__prettify_string,__table;

    napi_create_object(env, &bs4_object);
    napi_create_function(env, "InitBs4", NAPI_AUTO_LENGTH, Init_BeautifulSoup, NULL, &init_bs4);
    napi_create_function(env, "GetTitle", NAPI_AUTO_LENGTH, GetTitle, NULL, &get_title);
    napi_create_function(env, "Prettify", NAPI_AUTO_LENGTH, GetPrettify, NULL, &__prettify_string);
    napi_create_function(env, "Table", NAPI_AUTO_LENGTH, Html_Table, NULL, &__table);



    napi_set_named_property(env, bs4_object, "InitBs4", init_bs4);
    napi_set_named_property(env, bs4_object, "GetTitle", get_title);
    napi_set_named_property(env, bs4_object, "Prettify", __prettify_string);
    napi_set_named_property(env, bs4_object, "Table", __table);


    return bs4_object;
}

static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor bs4_property = {
"BeautifulSoup",
        NULL,
        CreateBS4Object,
        NULL,
        NULL,
        NULL,
        napi_default,
        NULL
    };
    napi_define_properties(env, exports, 1, &bs4_property);
    Py_Finalize();
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
