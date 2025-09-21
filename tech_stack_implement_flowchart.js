{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 ---\
config:\
  layout: fixed\
  theme: default\
  look: classic\
---\
flowchart TD\
 subgraph Frontend["<b>Frontend Layer: UI</b>"]\
        FE1["<b>HTML5 + CSS3 + JS (UI, dashboards, forms)</b>"]\
        FE2["<b>GDevelop/Scratch/Open-Source animations for quizzes &amp; retro visuals</b>"]\
        FE3["<b>Service Workers enable offline access</b>"]\
  end\
 subgraph GameLogic["<b>Game Logic Layer</b>"]\
        GL1["<b>Core quiz mechanics written in C++ or JavaScript</b>"]\
        GL2["<b>Compiled into WebAssembly (Wasm) gives near native speed</b>"]\
        GL3["<b>Runs inside browser for fast performance</b>"]\
        GL4["<b>Handles:<br>- Checking answers<br>- Updating scores/hearts<br>- Reward/penalty system</b>"]\
  end\
 subgraph Storage["<b>Data Storage Layer</b>"]\
        n6@\{ label: "<span style=\\"--tw-scale-x:\\"><span style=\\"--tw-scale-x:\\"><b>Local storage: SQLite/IndexedDB</b><br style=\\"--tw-scale-x:\\"></span></span><b>Stores quizzes, student progress, results offline</b>" \}\
        n3@\{ label: "<b>Central: MySQL server<br style=\\"--tw-scale-x:\\">Master question bank (already uploaded content + teacher uploads)<br style=\\"--tw-scale-x:\\">Student performance data for dashboards</b>" \}\
  end\
 subgraph Backend["<b>Backend Layer</b>"]\
        BE1["<b>Node.js + Express.js (REST APIs)</b>"]\
        BE2["<b>Syncs data between local SQLite and central MySQL</b>"]\
        BE3["<b>Handles login/authentication (JWT)</b>"]\
        BE4["<b>APIs for teacher uploads &amp; student performance</b>"]\
  end\
 subgraph Split[" "]\
    direction LR\
        Teacher["<b>Teacher Case<br>- Teacher logs in<br>- Uploads new questions (form)<br>- Data stored locally, synced to MySQL<br>- Views class dashboards, leaderboards, SWOT</b>"]\
        Student["<b>Student Case<br>- Student logs in<br>- Quizzes preloaded (teacher/already uploaded DB)<br>- Plays gamified quiz (C++/Wasm/JS logic)<br>- Progress stored locally, synced to central DB<br>- Views own dashboard only</b>"]\
  end\
    Frontend --> GameLogic\
    Split --> End(["<b>END</b>"])\
    Backend --> Split\
    Start(["<b>START</b>"]) --> n4@\{ label: "<span style=\\"--tw-scale-x:\\"><b>User(Teacher/Student) logs in the Progressive Web App</b></span>" \}\
    n4 --> Frontend\
    GameLogic --> Storage\
    Storage --> Backend\
    n1["<b>Implementation of Tech Stack at Different Layers of EduQuest</b>"]\
    n6@\{ shape: internal-storage\}\
    n3@\{ shape: db\}\
    n4@\{ shape: event\}\
    n1@\{ shape: rounded\}\
     Teacher:::usercase\
     Student:::usercase\
     Frontend:::layer\
     GameLogic:::layer\
     Backend:::layer\
     Storage:::layer\
     n1:::usercase\
     n1:::Aqua\
    classDef layer fill:#f5f5f7,stroke:#999,stroke-width:2px\
    classDef usercase fill:#e7f6d5, stroke:#338a2e\
    classDef Aqua stroke-width:1px, stroke-dasharray:none, stroke:#46EDC8, fill:#DEFFF8, color:#378E7A\
    style n1 color:#000000,fill:#00C853}
