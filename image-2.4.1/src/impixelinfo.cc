// Copyright (C) 2016 Eric Addison <ericaddison@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, see <http://www.gnu.org/licenses/>.

#include <octave/oct.h>
#include <octave/graphics.h>
#include <QtHandlesUtils.h>
#include <QtGui>
#include <Figure.h>
#include <Canvas.h>
#include <Container.h>
#include "Backend.h"
using QtHandles::Figure;
using QtHandles::Canvas;
using QtHandles::Backend;
using QtHandles::Container;

class impixelinfoEventFilter : public QObject
  {
  public:
  impixelinfoEventFilter():QObject()
  {
	  std::cout << "creating new filter\n";
  };
  ~impixelinfoEventFilter(){};

  bool eventFilter(QObject* object,QEvent* event)
  {
      //if(event->type() == QEvent::MouseMove)
      //{
	std::cout <<"Event.."<<std::endl;
	return true;
      //}
      //else 
      //{
	//return QObject::eventFilter(object,event);
      //}
  }; 
};

DEFUN_DLD (impixelinfo, args, ,"\
-*- texinfo -*-\n\
@deftypefn {Loadable Function}  impixelinfo(@var{bw1}, @var{c}, @var{r}, @var{n})\n\
\n\
@end deftypefn\n\
")
{
  octave_value_list retval;
  const int nargin = args.length ();
  gh_manager::auto_lock lock;

  if (nargin == 0 || nargin > 2)
    {
      print_usage ();
      std::cout << "But you tried!\n";
      return retval;
    }
	
  if (nargin == 1)
    {
      std::cout << "Graphics handle only case!\n";
      graphics_object obj = gh_manager::get_object (args(0));

      if (obj.valid_object ())
        {
    	  std::cout << "valid object!\n";

    	  std::cout << "Listing parents of obj properties:\n";
    	  		graphics_object o(obj);
    	  		for( int i=0; i<10; i++)
    	  		{
    	  			if(o.valid_object())
    	  			{
    	  				std::cout <<  "this object ... " << o.type() << "\n";

    	  				if(o.isa("figure"))
						{
    	  					std::cout << "Tryng to cast to figure... \n";
							Figure* fig =
									dynamic_cast<Figure*> (Backend::toolkitObject (o));
							std::cout << "mouse mode = " << fig->mouseMode() << "\n";

							std::cout << "Tryng to get a canvas... \n";
							Canvas* can = fig->innerContainer()->canvas(o.get_handle());
							can->toggleGrid(o.get_handle());
							impixelinfoEventFilter* filt = new impixelinfoEventFilter();
							can->qWidget()->installEventFilter(filt);
						}


    	  			}
    	  			o = gh_manager::get_object(o.get_parent());
    	  		}

        }

/*
      double dh = args(0).double_value ();
      if (! error_state)
        {
          std::cout << "Found graphics handle\n";
          graphics_handle gh = gh_manager::lookup(dh);
       
          if (gh.ok ())
            {   
              graphics_object obj = gh_manager::get_object (gh);
              if (obj.valid_object ())
                {
                  std::cout << "Found graphics object\n";
		std::cout << "obj type = " << obj.type() << "\n";
		graphics_object fig = obj.get_ancestor("figure");
		if ( fig.isa("figure"))
                  std::cout << "Found graphics parent figure\n";
		else
                  std::cout << "nope\n";
		
		// see if it's some type of object
                Figure* Fig =
                  dynamic_cast<Figure*> (Backend::toolkitObject (fig));


		// see what BAckend thinks it is
		std::cout << "What is obj? fig? " << QtHandles::toolkitObjectProperty(obj) << " -- " << QtHandles::toolkitObjectProperty(fig) << "\n";
		QString val = QString("Hello");

		std::cout << "Listing parents of obj properties:\n";
		graphics_object o(obj);
		for( int i=0; i<10; i++) {
			std::cout <<  "this object... " << QtHandles::toolkitObjectProperty(o) << "\n";
			o = gh_manager::get_object(o.get_parent());
			impixelinfoEventFilter* filt = new impixelinfoEventFilter();
			dynamic_cast<Figure*> (Backend::toolkitObject (obj))->installEventFilter(filt);
		}
			
		Fig->updateStatusBar("test!");
		impixelinfoEventFilter* filt = new impixelinfoEventFilter();
		Fig->installEventFilter(filt);


	  QList<graphics_object> axesList;
	  Matrix children = obj.get_properties ().get_all_children ();
	  octave_idx_type num_children = children.numel ();
	  graphics_object currentObj, axesObj;

	  for (int i = 0; i < num_children; i++)
		{
		  graphics_object childObj (gh_manager::get_object (children(i)));

		  if (childObj.isa ("axes")){
			  std::cout << "Found an axes\n";
			axesList.append (childObj);
		  }
		  else if (childObj.isa ("uicontrol") || childObj.isa ("uipanel"))
			{
			  Matrix bb = childObj.get_properties ().get_boundingbox (false);
			  QRectF r (bb(0), bb(1), bb(2), bb(3));

			  r.adjust (-5, -5, 5, 5);
			//  if (r.contains (event->posF ()))
			//	{
			//	  currentObj = childObj;
			//	  break;
			//	}
			}
		}

*/

//      {
//        select_object (obj, event, currentObj, axesObj);
/*
        if (axesObj.valid_object ())
          {
            axes::properties& ap = Utils::properties<axes> (axesObj);
            ColumnVector v = ap.pixel2coord (event->x (), event->y ());
            QString val = QString ("");
            if (currentObj.isa ("image"))
              {
                octave_value xdata = currentObj.get ("xdata");
                octave_value ydata = currentObj.get ("ydata");
                octave_value cdata = currentObj.get ("cdata");
                int x = floor (xdata.size ()(0) * v(0)
                               / xdata.matrix_value()(xdata.size ()(0)-1) - 0.5);
                int y = floor (ydata.size ()(0) * v(1)
                               / ydata.matrix_value ()(ydata.size ()(0)-1) - 0.5);
                val = QString (" : %1").arg (cdata.matrix_value ()(y,x),0,'g',5);
              }
            fig->updateStatusBar (v,val);
          }
*/
//      }
 
      return retval;
    }

  if (nargin == 2)
    {
      std::cout << "Graphics handle and parent case!\n";
      return retval;
    }
      
  return retval;
}
