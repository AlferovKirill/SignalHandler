<h1 align="center">What is it?</h1>
<p align="justify">This is my summer internship project at a cool and well-known Russian aviation company. The task was to create an application for formation and correlation processing of LFM radar signals with realization of inter-network interaction between separate modules.</p>

<p align="justify">Stages of the task:</p>
<ol>
  <li align="justify">Collaborative development and integration with using Git version control tools.</li>
  <li align="justify">Mathematical modeling of reflected LFM radar signals from point radar targets radar targets with subsequent realization on C++/Qt5.</li>
  <li align="justify">Implementation of a module for the reception of reflections radar signals and their subsequent visualization based on Qt5 framework and Qwt library.</li>
  <li align="justify">Organization of network communication via Ethernet protocol Ethernet between the main modules of the program.</li>
  <li align="justify">Realization of algorithms of coordinated filtering of received radar signals and their visualization in the program interface with provision of possibility of displaying specific values of points on the graph, maximum signal level and side lobe levels of the compressed signal side lobes of the compressed signal.</li>
</ol>

<h1 align="center">How to install?</h1>
<p align="justify">It is assumed that you are already familiar with C++, Qt and have basic console skills. However, if this is not the case and you don't know much about the subject, or just don't want to bother, just copy the following commands into your terminal (for Debian or Ubuntu like).</p>

<p align="justify">To install Qt and QtCreator:</p>
```console
sudo apt install qtbase5-dev
sudo apt install qtcreator
```

<p align="justify">To install a few necessary libs:</p>
```console
sudo apt install libfftw3-dev
sudo apt install libqwt-qt5-dev
```

<h1 align="center">How does it work?</h1>

<img src="https://user-images.githubusercontent.com/59083480/255423011-33064b57-adb7-4ae7-bb6a-51a10a7c6ac2.png">
<p align="center">Sender demonstration work in network</p>

<img src="https://user-images.githubusercontent.com/59083480/255423013-1ed6e458-b671-4723-b95a-0fa298eda371.png">
<p align="center">Receiver demonstration work in network</p>

<img src="https://user-images.githubusercontent.com/59083480/255423725-f32a0db8-7cee-4d99-809b-855846bcc46a.mp4">
<p align="center">Demonstration video in local</p>
