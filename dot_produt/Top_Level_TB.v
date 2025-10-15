`timescale 1ns / 1ps

module tb_Top_Level;

    // Inputs
    reg clk;
    reg rst;
    reg SW12, SW13, SW14, SW15;
    reg [7:0] SW;
    reg [1:0] SW_digit;

    // Outputs
    wire [15:0] LED;
    wire an0, an1, an2, an3;
    wire dp;
    wire oflow;
    wire [6:0] cathode;

    integer i;

    // Instantiate DUT
    Top_Level uut (
        .clk(clk),
        .rst(rst),
        .SW12(SW12),
        .SW13(SW13),
        .SW14(SW14),
        .SW15(SW15),
        .SW(SW),
        .SW_digit(SW_digit),
        .LED(LED),
        .an0(an0),
        .an1(an1),
        .an2(an2),
        .an3(an3),
        .dp(dp),
        .cathode(cathode)
    );

    // Clock gen: 100 MHz (10 ns period)
    initial clk = 0;
    always #5 clk = ~clk;

    // Stimulus
    initial begin
        // VCD dump
        $dumpfile("tb_Top_Level.vcd");
        $dumpvars(0, tb_Top_Level);

        i = 0;
        rst = 0;
        SW12 = 0; SW13 = 0; SW14 = 0; SW15 = 0;
        SW = 8'd0;
        SW_digit = 2'd0;
        
        #50;

        // Apply reset
        rst = 1;
        #50;
        rst = 0;
        #50;

        // Load A = 0x01020304
        SW12 = 1; SW13 = 0; SW14 = 0;
        SW = 8'd1; SW_digit = 2'd0; #50; // A[31:24] = 0x01
        SW = 8'd2; SW_digit = 2'd1; #50;
        SW = 8'd3; SW_digit = 2'd2; #50;
        SW = 8'd4; SW_digit = 2'd3; #50;
        SW12 = 0; #50;
        // Load B = 0x05060708
        SW13 = 1; SW14 = 0;
        SW = 8'd5; SW_digit = 2'd0; #50;
        SW = 8'd6; SW_digit = 2'd1; #50;
        SW = 8'd7; SW_digit = 2'd2; #50;
        SW = 8'd8; SW_digit = 2'd3; #50;
        SW13 = 0; #50;
        // Wait for MAC to compute
        #500;
        // Check results
        rst = 1; #50; rst = 0; #50;

        SW12 = 1; SW13 = 0; SW14 = 0;
        SW = 8'd10; SW_digit = 2'd0; #50;
        SW = 8'd11; SW_digit = 2'd1; #50;
        SW = 8'd12; SW_digit = 2'd2; #50;
        SW = 8'd13; SW_digit = 2'd3; #50;
        SW12 = 0; #50;
        SW13 = 1; SW14 = 0;
        SW = 8'd14; SW_digit = 2'd0; #50;
        SW = 8'd15; SW_digit = 2'd1; #50;
        SW = 8'd1; SW_digit = 2'd2; #50;
        SW = 8'd2; SW_digit = 2'd3; #50;
        SW13 = 0; #50;
        // Wait for MAC to compute
        #500;
        SW12 = 1; SW13 = 0; SW14 = 0;
        SW = 8'd255; SW_digit = 2'd0; #50;
        SW = 8'd255; SW_digit = 2'd1; #50;
        SW = 8'd255; SW_digit = 2'd2; #50;
        SW = 8'd255; SW_digit = 2'd3; #50;
        SW12 = 0; #50;
        SW13 = 1; SW14 = 0;
        SW = 8'd255; SW_digit = 2'd0; #50;
        SW = 8'd255; SW_digit = 2'd1; #50;
        SW = 8'd255; SW_digit = 2'd2; #50;
        SW = 8'd255; SW_digit = 2'd3; #50;
        SW13 = 0; #50;

        #500;

        SW12 = 1; SW13 = 0; SW14 = 0;
        SW = 8'd255; SW_digit = 2'd0; #50;
        SW = 8'd255; SW_digit = 2'd1; #50;
        SW = 8'd255; SW_digit = 2'd2; #50;
        SW = 8'd255; SW_digit = 2'd3; #50;
        SW12 = 0; #50;
        SW13 = 1; SW14 = 0;
        SW = 8'd255; SW_digit = 2'd0; #50;
        SW = 8'd255; SW_digit = 2'd1; #50;
        SW = 8'd255; SW_digit = 2'd2; #50;
        SW = 8'd255; SW_digit = 2'd3; #50;
        SW13 = 0; #50;

        begin
            rst = 0;
            for (i = 0; i < 3; i = i + 1) begin
                rst = 1; #(2);
                rst = 0; #(2);
            end
            rst = 1; #(40);
            for (i = 0; i < 3; i = i + 1) begin
                rst = 0; #(2);
                rst = 1; #(2);
            end
            rst = 0;
            #50;
        end 

        $finish;
    end

endmodule
