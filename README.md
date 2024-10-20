In this repository you can find the software created to simulate the Bethe Block, in order to create an algorithm that can be implemented also on an FPGA.
Since the ROOT libraries are used, in order to compile it uses the following command:

$ g++ main.cpp Libraries/Bethe_Block.cpp Libraries/DataSet.cpp  `root-config --cflags --glibs`

The Bethe-Block formula is:
![immagine](https://github.com/user-attachments/assets/6c231b8a-74ba-473f-825d-de2c50529795)



