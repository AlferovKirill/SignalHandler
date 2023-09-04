<h1 align="center">What is it?</h1>
<p align="justify">This is my assignment for a summer production practice. The task was to create an application for formation and correlation processing of LFM radar signals with implementation of inter-network interaction between separate modules.</p>

<p align="justify">Stages of the task:</p>
<ol>
  <li align="justify">Collaborative development and integration using Git version control tools.</li>
  <li align="justify">Mathematical modeling of reflected radar LFM signals from point targets with implementation based on fftw3 and C++/Qt5.</li>
  <li align="justify">Implementation of a module for reception of reflections of radar signals and their subsequent visualization based on Qt5 framework and Qwt library.</li>
  <li align="justify">Organization of network communication via Ethernet protocol between the main modules of the program.</li>
  <li align="justify">Implementation of Received Radar Signals Coordinated Filtering algorithms and their visualization in the program interface with provision of possibility of displaying specific values of points on the graph, the maximum signal level and the levels of the side lobes of the compressed signal.</li>
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

<p align="justify">Congratulations, you've downloaded all the stuff you need. Now all that's required is to download the project, you can do this via the website itself or again via the console as shown below, having first moved to the directory where you want to work with the project.</p>

```console
git clone https://github.com/AlferovKirill/SignalHandler
```

<h1 align="center">How does it work?</h1>

<img src="https://github.com/AlferovKirill/SignalHandler/assets/59083480/60f06de8-5ebc-44ac-b5a9-5ab527e38506">
<p align="center">Sender demonstration work in network</p>

<img src="https://github.com/AlferovKirill/SignalHandler/assets/59083480/095da701-ade6-4fd8-bbf6-f888950b0f63">
<p align="center">Receiver demonstration work in network</p>

https://github.com/AlferovKirill/SignalHandler/assets/59083480/ce9b1e6d-d54f-43b1-8a8e-81e88e68ae6e
<p align="center">Demonstration video in local</p>
