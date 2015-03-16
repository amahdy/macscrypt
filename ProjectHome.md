# MACSCrypt #
Powerful cryptography algorithms implementation, with several user interfaces for the demonstration, but you still can access each separate algorithm from a simple API, you can even have a single library for specific algorithm without needing to include everything ...

**Integrating MACSCrypt into your code is very simple, it's just one line code needed:**

```
//DEFINING THE OBJECT:
MACSCrypt macsCryptObj = new MACSCrypt();

//DEFINING ALGORITHM AND MODE:
macsCryptObj.Algorithm = MACSCrypt::CALGORITHM::AES; //Or DES or DES3 or AES3(NEW!) and implementing ...
macsCryptObj.Mode = MACSCrypt::CMODE::EBC; //Or CBC or CTR or OFB or much more, and inventing ...

/*** AND here is the line: ***/

//Encryption:
stringOutPut = macsCryptObj.Encrypt(strPlainText, strKey, numberOfRounds, 0); //0 because it's not a file input
/*** OR ***/
//Decryption:
stringOutPut = macsCryptObj.Decrypt(strCypherText, strKey, numberOfRounds, 0); //0 because it's not a file input

//Koool? and yes it supports files too!
```


---

**News:**

  * 2009.04.26 DES to encrypt anything using anykey, just pass any-object, will be encrypted ;)
  * 2009.04.03 Major changes in both data structure and logic structure of DES to increase the performance and decrease the used memory.
  * 2009.03.28 Re-organization in the svn repository, now it looks nicer.
  * 2009.03.28 Updates and some fixes in the DES.
  * 2009.03.12 A AES stand-alone demo source code has been released.
  * 2009.03.01 A DES stand-alone demo source code has been released.
  * 2009.02.28 DLL source code has been released.
  * 2009.02.28 DLL executable is available for download.
  * 2009.02.28 GUI executable is available for download.
  * 2009.02.26 GUI+DLL executables are available for download.

**Notes:**

  * Currently the source code is ~~not available, only a GUI demonstration using C++.Net, you can use the bundled dll to link to the several supported algorithms, more details will be available soon AFTER the release of the source code~~ available for the dll ~~only~~ and each separate algorithm source code is available too, written to compile for ~~.Net 3.5~~ any standard C++03 compiler, and you can now download a compiled GUI that demonstrate the dll.
  * More platforms ~~will be~~ are supported ~~later~~ now, currently under windows using .Net Framework 3.5 you can easily link to the bundled dll, and under any other platform you can compile the source independently.

**Project Status:**

  * Releasing a PUBLIC version of the source code to meet the C++03 standards.

**Project Development Steps:**

  * Algorithms Implementation. _DONE_
  * New Invented Algorithms Implementation. _DONE_
  * Simple GUI Demonstration. _DONE_
  * Featured GUI Demonstration. _DONE_
  * Core Standardization. _CURRENT_
  * Command Line Support. _PENDING_
  * Plug-In Concept Support. _PENDING_
  * Operating System Portability Management. _PENDING_
  * Other Languages Support With Simple UI Demonstrations, in the following order:
    1. JAVA _PENDING_
    1. C-Sharp _PENDING_
    1. VB.Net _PENDING_
    1. VB6 _PENDING_
    1. ASP.Net _PENDING_
    1. PHP _PENDING_
    1. PERL _PENDING_
  * Featured UI's. _PENDING_

---


MACS stands for "Math And Computer Science", the logic used comes from here, actually the project was originally developed as a graduation project by 2 Egyptian Computer-Science students: (Amahdy & Paula), special thanks to (Haly) ...

_I hope u enjoy it, and share your thoughts and feedback :)_