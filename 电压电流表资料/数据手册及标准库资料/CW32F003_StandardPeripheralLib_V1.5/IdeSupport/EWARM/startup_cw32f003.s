
;/*****************************************************************************/
;/*  Startup for IAR                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2021-02-24                                                   */
;/*  Target-mcu  M0+ Device                                                   */
;/*****************************************************************************/


                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                SECTION .intvec:CODE:ROOT(8)
                DATA
__vector_table
                DCD     sfe(CSTACK)               ; Top of Stack
                DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in

                DCD     WDT_IRQHandler
                DCD     LVD_IRQHandler
                DCD     0
                DCD     FLASHRAM_IRQHandler
                DCD     SYSCTRL_IRQHandler
                DCD     GPIOA_IRQHandler
                DCD     GPIOB_IRQHandler
                DCD     GPIOC_IRQHandler
                DCD     0
                DCD     0
                DCD     0
                DCD     0
                DCD     ADC_IRQHandler
                DCD     ATIM_IRQHandler
                DCD     VC1_IRQHandler
                DCD     VC2_IRQHandler
                DCD     GTIM_IRQHandler
                DCD     0
                DCD     0
                DCD     0
                DCD     BTIM1_IRQHandler
                DCD     BTIM2_IRQHandler
                DCD     BTIM3_IRQHandler
                DCD     I2C_IRQHandler
                DCD     0
                DCD     SPI_IRQHandler
                DCD     0
                DCD     UART1_IRQHandler
                DCD     UART2_IRQHandler
                DCD     0
                DCD     AWT_IRQHandler
                DCD     0

                THUMB

                PUBWEAK Reset_Handler
                SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                LDR     R1, =0X0
				LDR     R0, [R1] 
                MOV     SP, R0
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0

                PUBWEAK NMI_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
                B       HardFault_Handler


                PUBWEAK SVC_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
                B       SysTick_Handler

 
                PUBWEAK WDT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
WDT_IRQHandler
                B       WDT_IRQHandler


                PUBWEAK LVD_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
                B       LVD_IRQHandler


                PUBWEAK FLASHRAM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
FLASHRAM_IRQHandler
                B       FLASHRAM_IRQHandler


                PUBWEAK SYSCTRL_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SYSCTRL_IRQHandler
                B       SYSCTRL_IRQHandler


                PUBWEAK GPIOA_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
GPIOA_IRQHandler
                B       GPIOA_IRQHandler


                PUBWEAK GPIOB_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
GPIOB_IRQHandler
                B       GPIOB_IRQHandler


                PUBWEAK GPIOC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
GPIOC_IRQHandler
                B       GPIOC_IRQHandler

                PUBWEAK ADC_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler
                B       ADC_IRQHandler


                PUBWEAK ATIM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
ATIM_IRQHandler
                B       ATIM_IRQHandler


                PUBWEAK VC1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC1_IRQHandler
                B       VC1_IRQHandler


                PUBWEAK VC2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
VC2_IRQHandler
                B       VC2_IRQHandler


                PUBWEAK GTIM_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
GTIM_IRQHandler
                B       GTIM_IRQHandler


                PUBWEAK BTIM1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
BTIM1_IRQHandler
                B       BTIM1_IRQHandler


                PUBWEAK BTIM2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
BTIM2_IRQHandler
                B       BTIM2_IRQHandler


                PUBWEAK BTIM3_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
BTIM3_IRQHandler
                B       BTIM3_IRQHandler


                PUBWEAK I2C_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
I2C_IRQHandler
                B       I2C_IRQHandler


                PUBWEAK SPI_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
SPI_IRQHandler
                B       SPI_IRQHandler


                PUBWEAK UART1_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
                B       UART1_IRQHandler


                PUBWEAK UART2_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
                B       UART2_IRQHandler


                PUBWEAK AWT_IRQHandler
                SECTION .text:CODE:NOROOT:REORDER(1)
AWT_IRQHandler
                B       AWT_IRQHandler


                END
