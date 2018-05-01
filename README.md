# opticfiber(Prototype)

author @Victor Mourão

# A program to control a pic18f4550 and count interrupts of light between two optic fibers.
# This code set an LCD 2x16 to show time counter in miliseconds and stop counting when the light is interrupted 
      3 times(The counter starts at 0 and ends at 3. So this is going to stops only after 4 interrupts. It needs to be fixed yet).
# The countmr() routine count the time and It is activated when there's an interrupt at TIMER0(TIMER0 is set inside main routine).
# The botao() routine is the interrupt at RB1 pin. In the ISIS design, It is a button that simulate a photodiode recieving the 
      light from the opctic fiber.
# The setPin() routine set the pif18f4550 configs.
# The delayM() routine is designed to slow the instructions speed to set the LCD configs at set_LCD() routine.
# The converte(int c) converts an integer to ASCII character and the result is used to set LCD characters in these routines:
      contaMil_un(), contaMil_dez(), contaMil_cent(), contaMil_mil(), contaSeg_un(), contaSeg_dez(), contaMin_un() and contaMin_dez().
      Those routines are used in the mostraNumero() routine to show on the LCD the time counting in miliseconds.
# The mostravolta() routine shows a message in Portuguese/BR and the Interrupt counter at that moment.
# Finally, the main() routine calls four routines setPin(), set_LCD(), mostravolta() and mostraNumero(). The two last routines are called
      inside the while(1) loop.
