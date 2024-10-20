In this repository you can find the software created in order to estimate the charge of a particle with a defined `&beta;` that crosses a thin amount of silicon loosing `&Delta;`E of energy using the Bethe-Block formula:
![immagine](https://github.com/user-attachments/assets/6c231b8a-74ba-473f-825d-de2c50529795)

Even if they are implemented as additional features in the software, in first approximation no corrections (`&#948;`) have been considered.

The program has been used to find an enoght precise algorithm to be implemented on an FPGA. 

Since the ROOT libraries are used, in order to compile it uses the following command:

$ g++ main.cpp Libraries/Bethe_Block.cpp Libraries/DataSet.cpp  `root-config --cflags --glibs`


The software contains also a part to simulate `&beta;` and `&Delta;`E of N charged particles


