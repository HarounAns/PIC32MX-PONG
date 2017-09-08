# PIC32MX-PONG
DRUM HERO by Haroun Ansari
Video link: https://www.youtube.com/watch?v=vYrzhxK3rLk&feature=youtu.be

My implementation of Drum Hero works as follows. The splash screen saying my name,
class, name of the game, and a clock that counts up to 5 in deciseconds. After the 5 seconds in
it goes the menu difficulty screen where it lets you choose between 3 difficulties. Easy, Medium,
and Hard. I wanted the game to be playable, so the hard mode isn’t that extremely difficult.
However the easy mode is very, very easy. The difficulty corresponds with the speed of the
“notes” as they approach the scorezone. The easy mode moves with a velocity of 1
pixel/decisecond. The medium and hard difficulties move with a velocity of 2 and 3 p/ds
respectively. This way the speed increases one p/ds with every increase in difficulty. Increasing
to 4 p/ds made the game rather difficult to play.

![Image of Difficulty levels](https://github.com/HarounAns/PIC32MX-PONG/blob/master/images/image1.PNG "Image of difficulty levels")

To navigate the menu press button 1 in order to
navigate the menu. Press button 2 in order to start the game over the desired difficulty.
For the actual game play you have 2 dotted lines which divide the pixel into 3 separate
sections. The top corresponds to the area where a Right Twist is hit, the bottom is for a Left
Twist, and the middle is for a double tap. I could not configure the double tap correctly, so I
replaced it with hitting button 2 to simulate it instead. A hobby of mine is Archery, so I decided to
make my “notes” arrow tips. The zones are marked with a “R”, “D”, and “L” from top to bottom to
correspond to the motion that is required to score points. There is also a score zone which is a
large white rectangular box that spans from pixel 108 to 111. When arrows are in the score
zone and you apply the twists and the double tap, the score is incremented by 500. Also if you
score an asterisk (*) will be output on the end of the scorezone. If you miss the arrow and it
passes the end of the score zone (pixel 111), then you will be decremented by 100 points, and
an output of a larger arrow tip, which is denoted by a greater than sign character (>) will be
output at the end of the scorezone. Audience feedback (AFB on the OLED) is denoted by happy
and sad faces. If you get a streak of 4 in a row you will get a smiley face * :) *. If you get a streak
of 8 in a row you get a very happy smiley face :D . If you get a miss streak of 4 you get a sad
face ): . If you miss 8 in a row you get a very sad face D: . If you dont have any of those streaks
then you get a neutral face :| . After a minute is over the game finishes and a screen comes that
tells you your score. After that it takes you back to the difficulty screen.

![Image of Gameplay](https://github.com/HarounAns/PIC32MX-PONG/blob/master/images/image2.PNG)

Extra feature: Secret God Mode
This game mode is accessed when you are in the difficulty screen and you perform a
right twist 3 times. The screen will blink every time you perform a right twist. If you do it
successfully you will end up on the Secret Menu, which prompts you to press button 1 in order
to enter the game. If you press button 2 you end back up on the difficulty screen. Secret God
Mode allows a “ Drum Hero God” to play the game. There is no user interaction, because the
God plays the game for you. When an arrow moves over the scorezone, it flashes, designating
that the God has pressed over it. An asterisk or the arrow will still be displayed on the other side
of the score zone, but don’t hold your breath for an arrow to come on the other side, because
the Drum Hero God never misses!
