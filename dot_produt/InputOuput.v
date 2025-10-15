`timescale 1ns / 1ps

module InputOutput(
    input clk,
    input rst,
    input SW12,
    input SW13,
    input [7:0] SW,
    input [1:0] SW_digit,
    output reg [7:0] A,
    output reg [7:0] B,
    output reg [31:0] A_entire,
    output reg [31:0] B_entire,
    output mac_enable
);

reg [3:0] A_counter;
reg [3:0] B_counter;
reg [2:0] counter;

wire initiate_mac;
wire dot_product_computed;

assign initiate_mac = (A_counter == 4'b1111) && (B_counter == 4'b1111);
assign mac_enable = initiate_mac && ~dot_product_computed;
assign dot_product_computed = (counter > 4);

always @(posedge clk) begin
    if (rst) begin
        A_entire = 32'd0;
        B_entire = 32'd0;
        A_counter <= 3'd0;
        B_counter <= 3'd0;
    end 

    else begin

        if (counter >= 4) begin
            A_counter <= 4'd0;
            B_counter <= 4'd0;
        end

        if (SW12) begin
            case (SW_digit)
            2'd0: begin
                A_entire[31:24] <= SW;
                A_counter[3] <= 1'b1;
            end
            2'd1: begin
                A_entire[23:16] <= SW;
                A_counter[2] <= 1'b1;
            end
            2'd2: begin
                A_entire[15:8] <= SW;
                A_counter[1] <= 1'b1;
            end
            2'd3: begin
                A_entire[7:0] <= SW;
                A_counter[0] <= 1'b1;
            end 
            default: ;
            endcase
        end

        if (SW13) begin
            case (SW_digit)
            2'd0: begin
                B_entire[31:24] <= SW;
                B_counter[3] <= 1'b1;
            end
            2'd1: begin
                B_entire[23:16] <= SW;
                B_counter[2] <= 1'b1;
            end
            2'd2: begin
                B_entire[15:8] <= SW;
                B_counter[1] <= 1'b1;
            end
            2'd3: begin
                B_entire[7:0] <= SW;
                B_counter[0] <= 1'b1;
            end
            default: ;
            endcase
        end
    end
end

always @(posedge clk) begin
    if (rst) begin
        A <= 8'd0;
        B <= 8'd0;
        counter <= 3'd0;
    end
    else if ((counter < 4) && initiate_mac) begin 
        case (counter) 
            2'd0: begin
                A <= A_entire[31:24];
                B <= B_entire[31:24];
            end
            2'd1: begin
                A <= A_entire[23:16];
                B <= B_entire[23:16];
            end
            2'd2: begin
                A <= A_entire[15:8];
                B <= B_entire[15:8];
            end
            2'd3: begin
                A <= A_entire[7:0];
                B <= B_entire[7:0];
            end
        endcase
        counter <= counter + 1;
    end

    else if (counter >= 4) begin
        counter <= 3'd0;
    end
end

endmodule
