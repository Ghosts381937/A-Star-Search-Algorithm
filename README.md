# A-Star-Search-Algorithm
平面圖型上，有多個節點的路徑，求出最低通過成本的演算法。常用於遊戲中的NPC的移動計算。結合Best-first search & Dijikstra的優點，進行啟發式搜尋提高演算法效率的同時，可以保證找到一條最佳路徑（基於評估函式）。(圖文擷取自A*搜尋演算法 – 維基百科，自由的百科全書 (wikipedia.org))

演算法:  
&nbsp;&nbsp;&nbsp;&nbsp;前置:  
&nbsp;&nbsp;&nbsp;&nbsp;將會有3個變數控制著節點移動:FGH  
&nbsp;&nbsp;&nbsp;&nbsp;F:G+H  
&nbsp;&nbsp;&nbsp;&nbsp;G:某節點至起點的距離  
&nbsp;&nbsp;&nbsp;&nbsp;H:某節點至終點的距離  
&nbsp;&nbsp;&nbsp;&nbsp;簡述:以G+H得出的最短距離即F來確認路徑為最低cost直到最終走訪至終點為止。

詳細步驟:  
&nbsp;&nbsp;&nbsp;&nbsp;1.建立一維的Open List(存放即將走訪的節點，及對應的F)、二維的Closed List矩陣(存放尚未走訪的節點)、及一個二維矩陣Detail存放FGH及路徑(parent_i,parent_j)，並且將起點放入Open List及Detail並且將parent_i,parent_j指向自己。  
&nbsp;&nbsp;&nbsp;&nbsp;2.While(Open List不為空)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.1從Open List前端取出一個節點設為q  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.2於Closed List裡將q設為已走訪  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.3從q延伸找出8個方向的節點(上、下、左、右、上左、上右、下左、下右)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4 for(8個方向節點)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.1 If若該節點為終點則將q設為該節點之parent並且離開While  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.2 Else if若該節點可走訪（也許有阻隔）並且Closed List為未走訪狀態，該節點Gtmp = q.G + 該節點至q的距離 ，tmp = 終點至該節點的距離（註１），Ftmp = Gtmp + Htmp  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.4.2.1 If若於Detail裡該節點的F為初始值或是F > Ftmp(即新路徑長較短)，則將Gtmp、Htmp、Ftmp、parent_i、parent_j填入，並且將該節點放入Open List尾端
  
註1:常見使用3種距離計算的方式:1.Manhattan Distance,2.Diagonal Distance,3.Euclidean Distance
