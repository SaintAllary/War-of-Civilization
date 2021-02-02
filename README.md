[COURSE WORK]</br>
#C #C++ #OpenGL #Cource Work #SFML #Game #Team project</br>


We with my friend after learning programming for 3 month wanted to create some game </br>
UE4 is too hard to learn in short terms, that is why we decide to use some kind of graphic lib </br>
And finally we found. SFML free lib that is cross-platform and based on low-level OpenGL </br>
to tell the truth this lib is very bad, how we understood later (I'm talking about speed of </br>
developing and work-speed (basic empty window without any kind of properties takes 40% of GPU, my GC: 1050 GTX)).SFML gave us permission to 
native event loop and we have to work with it</br>
 </br>
 
 </br>Concept was of creating clone of legendary game Civilization 1 </br>
 </br>I don't think that any of u'll download this repo, that is why </br>
 I won't write about inteface a lot</br>
 I just will say that we did to much, my friend had a lot of problems </br>
 that is why I wrote 70% of project by myself </br>
 
  </br>In short preview we can: </br>
  -Start new game </br>
  -Continue prev </br>
  -Load any game </br>
  -Exit

 </br>In game we can: </br>
-Press esc to see menu
-Press enter to skipp turn
-Press tab to watch hotkeys </br> </br>
-Build town </br>
-Destroy town </br>
-Take over the town (and build in this town building and new units </br>
-Build several units with several features </br>
-Units can: move,attack,sleep,regenerate(not all units and only in town) (every units take supply and money to contain them)

</br>More about town:</br>
-Town that you build or take over will produce you: supply, money,science,culture</br>
-All produced things depend on the position (point on the map)</br>
-Every town know what kind of units he produced, where they are and how much money it needs to contain them</br>
-Every town can build several building that can boost a lot, for example wall give you a lot of protection</br>
(Example: Imagine that town was build on the hill and without walls 2 legioners can take over it, but</br>
with walls even 5 legioners can be defeated vs town)
-On mountains (or any high ground) protection is much more higher, but on low ground production is more high

</br>More about terrain and map:</br>
-Map is generated with some kind of Perlin Noise (algoritm you can google)
-Every cell of map has it's own terrain and features that can give more production,protection,gold,science etc.

</br>More about mechanics:</br>
-Fight any unit or town vs same depends on protection,position of the map, and it's own hp and armor
-Armor and health can be hit and only in town you can regenarate it
-After every kill unit get some rang and this rang boost his attack and armor max-lvl
-Surrounding give you boost of attack 

</br>Game saves in file *.tlog* that will contain all algorithm of saving and values)</br>
</br>Game has log system on f1</br>

</br>AI isn't very clever, but it always try to build town on the best place, and find enemies</br>

(I hope I recall all about game,wrote it year ago and maybe forget smth)


![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/1.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/2.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/3.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/4.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/5.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/6.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/7.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/8.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/9.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/10.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/11.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/12.jpg)
![Image alt](https://github.com/SaintAllary/War-of-Civilization/raw/master/ImagesGit/13.jpg)

