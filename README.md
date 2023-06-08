Secret Lock

What does the project do?

My project is a concealed lock that can be integrated into any object or location where additional security is needed. For example, a box, a door, or, in the case of the prototype for my project, a small jewelry box. By using a small jewelry box, I wanted to demonstrate that my lock prototype can be embedded anywhere.

The lock features a servo motor and a touch sensor button, enabling the setting and recognition of a secret knock, which is a sequence of strikes. The servo motor operates the lock mechanism, allowing the lid to be opened and closed. The system is powered by button cell batteries for convenience and portability.

One of the key functionalities of the lock is its ability to "memorize" the secret knock by recording the timing between strikes. Additionally, it can recognize excessively fast or slow inputs, ensuring accurate detection of the secret knock.

This hidden lock offers an innovative and versatile solution for enhancing security in various settings. Its discreet design and adaptable nature make it a valuable addition to safeguard belongings or restricted areas.



What I will need?

Instruments:

❏ Soldering Iron Kit 
❏ Soldering Tool Station 
❏ Jewellery box 
❏ Solder Wire Net 
❏ Wire Stripper 
❏ Nintendo Nano ATmega 328P

Other components:

❏ Micro Servo MG90S 
❏ AA Battery holder 
❏ Touch sensor button 
❏ Mosfet IRFZ44N 
❏ Computer Speaker 
❏ Resistor 100 Ohm 
❏ Resistor 10 k Ohm
❏ Super Glue 
❏ Drill 
❏ Paper Clip 
❏ Double-side tape 
❏ Hammer 
❏ Pliers



How will the project work?

The logic of my project is designed as follows: upon power connection, the recording function of the secret combination of strikes or knocks is initiated. All strikes and inputs are processed as interrupts, ensuring a high level of accuracy in recording and recognition. Initially, the system awaits the ﬁrst input. If a signal is received, it begins measuring the time between subsequent strikes and records them in its memory. If no signals are received within 3 seconds, the combination is considered complete. Subsequently, the recorded combination is replayed, the lid is closed, and the system enters a sleep mode to conserve energy.

Since interrupts are utilized, any triggering from the sensor will awaken the system and initiate the recognition of the secret knock by comparing the timing between strikes or inputs. To unlock the lock, the entire combination must match perfectly.



Idea formation:

Idea formation for the lock project involved a creative and iterative process to develop a concealed lock with a servo motor and touch sensor button for recognizing a secret knock sequence.

The following steps contributed to the formation and reﬁnement of this idea:

Identiﬁcation of the Problem: The initial idea formation stemmed from recognizing the need for enhanced security in various settings. Identifying the challenge of designing a versatile lock that could be integrated into any object or location became the foundation for the project.

Inspiration and Research: Gathering information on existing lock mechanisms, servo motors, and touch sensors provided inspiration and insights into available technologies. Researching similar projects and exploring different solutions stimulated creativity and sparked innovative ideas.

Prototyping and Testing: Building prototypes enabled the testing of different components and functionalities. The feedback obtained from the prototypes aided in reﬁning the design, optimizing the servo motor's movement, and ensuring accurate recognition of the secret knock.

Iteration and Feedback: Incorporating feedback from family members, throughout the development process helped identify areas for improvement and reﬁnement. This iterative approach ensured that the lock met the desired criteria of reliability, security, and ease of use.

Integration and Adaptability: The idea formation process also involved exploring the adaptability of the lock prototype. By using a small jewelry box as a demonstration, it showcased the lock's potential to be embedded in various objects or locations, emphasizing its versatility and practicality.

Through the idea formation process, the concealed lock with a servo motor and touch sensor button evolved from a concept into a tangible and functional solution for enhancing security. The combination of different steps enabled the development of an innovative and adaptable lock design that could be integrated into different objects or spaces to provide an additional layer of protection.



Iterative design:

Iterative design is a fundamental approach employed in the development of the lock project. It involves a cyclical process of creating, testing, and reﬁning the design through multiple iterations. This methodology allows for continual improvement and optimisation of the lock's functionality and performance.

By embracing iterative design principles, the lock project can beneﬁt from continuous improvement and innovation. It provides a systematic framework for identifying and addressing design ﬂaws, enhancing functionality, and optimising performance. Ultimately, the iterative design process leads to the creation of a high-quality, reliable, and user-centric lock solution.



Development process:

1. Requirements Deﬁnition:
- I speciﬁed what the lock should do, which combinations it should recognize, the actions to be taken upon successful unlocking or unsuccessful attempts.

2. Hardware Design:
- I determined the necessary components for my project, such as a servo motor, vibration sensor, button, buzzer, and others.
- I designed the circuitry for connecting the components to the microcontroller.

3. Software Design:
- I developed an algorithm for recognizing the secret "knock" combination and controlling the lock.
- Wrote a code for the microcontroller that performs the following tasks:
- Unlocked the lock upon system startup and await input of the secret combination.
- If the combination is not entered within 5 seconds, unlock the lock with a single "knock".
- After the combination is entered (with a 5-second timeout), the buzzer plays back the combination, and the lock closes.
- A secret combination of "knocks" is sufficient to open the lock.
- To close the lock, a single "knock" or pressing an internal button can be used.
- Implement the use of hardware interrupts for optimal recognition of "knocks".

4. Testing and Debugging:

- I tested the functionality of the lock by inputting various "knock" combinations and verifying the correct opening and closing of the lock.
- Veriﬁed the operation of the secret combination, timeouts, and other functions.
- Debuged any issues or errors that may arise during testing.

5. Documentation:

- I have created documentation that explains the development process, the circuit diagram, and a description of how the lock operates.
- Included information about the "knock" combinations and other lock features in the documentation.



Possible improvements:

To further enhance my project, I suggest replacing the sensor with a digital sound sensor. This will allow clapping hands to be used instead of knocks to recognize the combination. This approach will be more convenient and intuitive for users.

Additionally, I would like to add vibration sensors and conﬁgure the system in such a way that the lock can be opened using a speciﬁc device, such as a remote control. This will add convenience and enable opening the object from a distance.

Implementing these additional features will enhance the functionality of the project and expand its capabilities, providing more ﬂexibility and convenience in its use. Also, it will improve the ability of the locker security and mobility.
