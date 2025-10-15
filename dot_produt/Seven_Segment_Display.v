`timescale 1ns / 1ps

module Seven_Segment_Display (
    input clk,
    input rst,
    input oflow,
    input SW14,
    input SW15,
    input [1:0] SW_digit,
    input [31:0] A,
    input [31:0] B,
    input [15:0] dot_product,
    output an0,
    output an1,
    output an2,
    output an3,
    output dp,
    output reg [6:0] cathode
);

    reg [6:0] seg;
    reg [1:0] active_anode;
    reg [16:0] counter;
    reg [32:0] reset_counter;
    reg reset_display;

    // initial begin
    //     active_anode = 2'd0;
    //     counter = 17'd0;
    //     reset_counter = 32'd0;
    //     reset_display = 0;
    // end

    function [6:0] digit_to_segment;
        input [3:0] digit;
        begin
            case (digit) 
                4'd0: digit_to_segment = 7'b0000001; // 0
                4'd1: digit_to_segment = 7'b1001111; // 1
                4'd2: digit_to_segment = 7'b0010010; // 2
                4'd3: digit_to_segment = 7'b0000110; // 3
                4'd4: digit_to_segment = 7'b1001100; // 4
                4'd5: digit_to_segment = 7'b0100100; // 5
                4'd6: digit_to_segment = 7'b0100000; // 6
                4'd7: digit_to_segment = 7'b0001111; // 7
                4'd8: digit_to_segment = 7'b0000000; // 8
                4'd9: digit_to_segment = 7'b0000100; // 9
                4'd10: digit_to_segment = 7'b0001000; // A
                4'd11: digit_to_segment = 7'b1100000; // b
                4'd12: digit_to_segment = 7'b0110001; // C
                4'd13: digit_to_segment = 7'b1000010; // d
                4'd14: digit_to_segment = 7'b0110000; // E
                4'd15: digit_to_segment = 7'b0111000; // F
            endcase
        end
    endfunction

    function [6:0] number_to_print;
        input [1:0] digit;
        input [31:0] num;
        input half;
        begin
            case(half)
                0: begin
                    case (digit)
                        2'd0: number_to_print = digit_to_segment(num[31:28]);
                        2'd1: number_to_print = digit_to_segment(num[23:20]);
                        2'd2: number_to_print = digit_to_segment(num[15:12]);
                        2'd3: number_to_print = digit_to_segment(num[7:4]);
                    endcase
                end
                1: begin
                    case (digit)
                        2'd0: number_to_print = digit_to_segment(num[27:24]);
                        2'd1: number_to_print = digit_to_segment(num[19:16]);
                        2'd2: number_to_print = digit_to_segment(num[11:8]);
                        2'd3: number_to_print = digit_to_segment(num[3:0]);
                    endcase
                end
            endcase
        end
    endfunction

// initial begin
//    active_anode = 2'd0;
//    counter = 17'd0;
//    reset_counter = 32'd0;
//    reset_display = 0;
// end
// for simulation

assign dp = 1;
    
always @(posedge clk) begin
    if(rst) begin
        reset_counter <= 0;
        reset_display <= 1;
    end
    else if(reset_display) begin
        reset_counter <= reset_counter + 1;
        if(reset_counter > 32'd500_000_000) begin
           reset_display <= 0;
           reset_counter <= 0;
        end
    end
end

always @(posedge clk) begin
    counter <= counter + 1;
    if (counter == 17'd999999) begin
        counter <= 0;
        active_anode <= (active_anode==2'd3)? 2'd0 : active_anode + 1;
    end
end

    assign an0 = ~(active_anode == 2'd0);
    assign an1 = ~(active_anode == 2'd1);
    assign an2 = ~(active_anode == 2'd2);
    assign an3 = ~(active_anode == 2'd3);

always @(posedge clk) begin
    if (reset_display) begin
        case (active_anode)
            2'd0: cathode = 7'b1111110; // -
            2'd1: cathode = 7'b1111010; // r
            2'd2: cathode = 7'b0100100; // s
            2'd3: cathode = 7'b1110000; // t
        endcase
    end
    else if (oflow) begin
        case (active_anode)
            2'd0: cathode = 7'b0000001; // O
            2'd1: cathode = 7'b0111000; // F
            2'd2: cathode = 7'b1110001; // L
            2'd3: cathode = 7'b0000001; // O
        endcase
    end
    else if (SW14 && SW15) begin
        case (active_anode)
            2'd0: cathode = digit_to_segment(dot_product[15:12]);
            2'd1: cathode = digit_to_segment(dot_product[11:8]);
            2'd2: cathode = digit_to_segment(dot_product[7:4]);
            2'd3: cathode = digit_to_segment(dot_product[3:0]);
        endcase
    end
    else if (SW14) begin
        case (active_anode)
            2'd0: cathode = 7'b1111111; // blank
            2'd1: cathode = 7'b1111111; // blank
            2'd2: cathode = number_to_print(SW_digit, A, 0);
            2'd3: cathode = number_to_print(SW_digit, A, 1);
        endcase
    end
    else if (SW15) begin
        case (active_anode)
            2'd0: cathode = 7'b1111111; // blank
            2'd1: cathode = 7'b1111111; // blank
            2'd2: cathode = number_to_print(SW_digit, B, 0);
            2'd3: cathode = number_to_print(SW_digit, B, 1);
        endcase
    end
    else begin
        cathode = 7'b1111111;
    end
end

endmodule
