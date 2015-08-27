//
//  ViewController.h
//  sha1_test
//
//  Created by 구자은 on 2015. 8. 22..
//  Copyright (c) 2015년 0101RGB. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

-(IBAction)shaclicked:(UIButton *)sender;
-(IBAction)lshclicked:(UIButton *)sender;
@property(strong, nonatomic) IBOutlet UILabel* resultlabel;

@end

