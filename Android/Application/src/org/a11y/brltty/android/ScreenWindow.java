/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2018 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU Lesser General Public License, as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any
 * later version. Please see the file LICENSE-LGPL for details.
 *
 * Web Page: http://brltty.com/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

package org.a11y.brltty.android;

import java.util.Map;
import java.util.HashMap;

import android.view.accessibility.AccessibilityWindowInfo;
import android.view.accessibility.AccessibilityNodeInfo;

import android.graphics.Point;
import android.graphics.Rect;

public class ScreenWindow {
  private final static Map<Integer, ScreenWindow> windows =
               new HashMap<Integer, ScreenWindow>();

  private final Integer windowIdentifier;
  private AccessibilityWindowInfo windowObject = null;

  private ScreenWindow (Integer identifier) {
    windowIdentifier = identifier;
  }

  public static ScreenWindow get (Integer identifier) {
    synchronized (windows) {
      ScreenWindow window = windows.get(identifier);
      if (window != null) return window;

      window = new ScreenWindow(identifier);
      windows.put(identifier, window);
      return window;
    }
  }

  public static ScreenWindow get (AccessibilityWindowInfo object) {
    ScreenWindow window = get(object.getId());

    synchronized (window.windowIdentifier) {
      if (window.windowObject != null) window.windowObject.recycle();
      window.windowObject = AccessibilityWindowInfo.obtain(object);
    }

    return window;
  }

  public static ScreenWindow get (AccessibilityNodeInfo node) {
    if (ApplicationUtilities.haveLollipop) {
      AccessibilityWindowInfo window = node.getWindow();

      try {
        return get(window);
      } finally {
        window.recycle();
        window = null;
      }
    } else {
      return get(node.getWindowId());
    }
  }

  public final int getIdentifier () {
    return windowIdentifier;
  }

  public final Rect getLocation () {
    synchronized (windowIdentifier) {
      Rect location = new Rect();

      if (windowObject != null) {
        windowObject.getBoundsInScreen(location);
      } else {
        Point size = new Point();
        ApplicationUtilities.getWindowManager().getDefaultDisplay().getSize(size);
        location.set(0, 0, size.x, size.y);
      }

      return location;
    }
  }

  public boolean contains (Rect location) {
    return getLocation().contains(location);
  }
}
