`timescale 1ns / 1ps

module Top_Level (
    input clk,
    input rst,
    input SW12,
    input SW13,
    input SW14,
    input SW15,
    input [7:0] SW,
    input [1:0] SW_digit,
    output [15:0] LED,
    output an0,
    output an1,
    output an2,
    output an3,
    output dp,
    output [6:0] cathode
);

wire clean_out;
wire oflow;
wire [7:0] A;
wire [7:0] B;
wire [31:0] A_entire;
wire [31:0] B_entire;
wire mac_enable;

Seven_Segment_Display display0 (
    .clk(clk),
    .rst(clean_out),
    .oflow(oflow),
    .SW14(SW14),
    .SW15(SW15),
    .SW_digit(SW_digit),
    .A(A_entire),
    .B(B_entire),
    .dot_product(LED),
    .an0(an0),
    .an1(an1),
    .an2(an2),
    .an3(an3),
    .dp(dp),
    .cathode(cathode)
);

InputOutput io0 (
    .clk(clk),
    .rst(clean_out),
    .SW12(SW12),
    .SW13(SW13),
    .SW(SW),
    .SW_digit(SW_digit),
    .A(A),
    .B(B),
    .A_entire(A_entire),
    .B_entire(B_entire),
    .mac_enable(mac_enable)
);

MAC mac0 (
    .clk(clk),
    .rst(clean_out),
    .mac_enable(mac_enable),
    .A(A),
    .B(B),
    .LED(LED),
    .oflow(oflow)
);

Debouncing debounce0 (
    .clk(clk),
    .noisy_in(rst),
    .clean_out(clean_out)
);

endmodule
