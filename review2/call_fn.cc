#include </usr/include/python2.7/Python.h>
#include <stdlib.h>
#include <stdio.h>
#include<vector>
#include<string.h>
#include<iostream>
int main()
{
   // Set PYTHONPATH TO working directory
   setenv("PYTHONPATH",".",1);

   PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;


   // Initialize the Python Interpreter
   Py_Initialize();


   // Build the name object
   pName = PyString_FromString((char*)"sort");

   // Load the module object
   pModule = PyImport_Import(pName);


   // pDict is a borrowed reference 
   pDict = PyModule_GetDict(pModule);


   // pFunc is also a borrowed reference 
   pFunc = PyDict_GetItemString(pDict, (char*)"Sort");
   std::vector<std::vector<int> > xa = { { 3, 6, 7, 8, 9 }, { 1, 2, 3, 4, 5 } };
   struct neigh{
   std::string peru;
   double id;
   };
   //int x[3][4] = {0, 1 ,2 ,3 ,4 , 5 , 6 , 7 , 8 , 9 , 10 , 11};
   Py_ssize_t len = xa.size();
   std::vector<neigh> neigh_list;
   neigh_list.push_back({"akhilla",20.2});
   neigh_list.push_back({"veena",30.2});
   //printf("%snn\t%fnn\n",neigh_list[0].peru.c_str(),neigh_list[0].id);
   Py_ssize_t len1 = neigh_list.size();
   //printf("%zu\n",len1);
   PyObject *result = PyTuple_New(len);
   int cnt=0;
   for (auto vectorit = neigh_list.begin(); vectorit != neigh_list.end(); ++vectorit)
    {
        std::cout << vectorit->peru <<std::endl;
        PyObject *item = PyTuple_New(len1);
	PyTuple_SET_ITEM(item, 0, PyString_FromString(vectorit->peru.c_str()));
	PyTuple_SET_ITEM(item, 1, PyFloat_FromDouble(vectorit->id));
	PyTuple_SET_ITEM(result,cnt,item);
	cnt++;
    }
    
   
   if (PyCallable_Check(pFunc))
   {
       pValue=Py_BuildValue("(O)",result);
       PyErr_Print();
       printf("Let's give this a shot!\n");
       presult=PyObject_CallObject(pFunc,pValue);
       PyErr_Print();
   } else 
   {
       PyErr_Print();
   }
   
   printf("Result is %d\n",PyList_Check(presult));
   
   int count = (int) PyList_Size(presult);
   
   printf("count : %d\n",count);
   
   //std::vector<std::vector<double> > data;
   //std::vector<double> d_temp;
   std::vector<neigh> neigh_temp;
   if (PyList_Check(presult)) {
	for(Py_ssize_t i = 0; i < PyList_Size(presult); i++) {
		PyObject *value = PyList_GetItem(presult, i);
		if(PyList_Check(value)){
			PyObject *invalue1 = PyList_GetItem(value,0);
			PyObject *invalue2 = PyList_GetItem(value,1);
			neigh_temp.push_back({PyString_AsString(invalue1),PyFloat_AsDouble(invalue2)});
		}
		}}
		/*
		for(Py_ssize_t j=0;j<PyList_Size(value);j++){
			printf("mehhh");
			PyObject *invalue = PyList_GetItem(value,j);
			
			d_temp.push_back(PyFloat_AsDouble(invalue));
			printf("%lf\t",d_temp[j]);
		}
		data.push_back(d_temp);
		d_temp.clear();
		//data.push_back( PyFloat_AsDouble(value) );
		//printf("%lf\n",data[i]);
	}
	
   }
	}

	
	for(int ik=0;ik<data.size();ik++){
	printf("\n");
	for(int jk=0;jk<data[ik].size();jk++){
	printf("%lf\t",data[ik][jk]);
}
}
*/
	for (auto vectorit = neigh_temp.begin(); vectorit != neigh_temp.end(); ++vectorit)
    	{
        std::cout << vectorit->peru <<'\t'<<vectorit->id<<std::endl;
        //PyObject *item = PyTuple_New(len1);
        //PyTuple_SET_ITEM(item, 0, PyUnicode_FromString(vectorit->peru.c_str()));
        //PyTuple_SET_ITEM(item, 1, PyFloat_FromDouble(vectorit->id));
        //PyTuple_SET_ITEM(result,cnt,item);
        //cnt++;
    }

	
 
   Py_DECREF(pValue);

   // Clean up
   Py_DECREF(pModule);
   Py_DECREF(pName);

   // Finish the Python Interpreter
   Py_Finalize();


    return 0;
}
